#include "qproject.h"

#include "host/qprojecthost.h"

#include "xmlnode.h"
#include "host/qhostfactory.h"
#include "host/qabstracthost.h"
#include "host/qabstractwidgethost.h"
#include "language/qlanguagemanager.h"
#include "property/qstringproperty.h"
#include "language/qlanguage.h"
#include "data/qdatamanager.h"
#include "stylesheet/qstylesheetmanager.h"

#include <QFile>
#include <QVariant>
#include <QUuid>
#include <QDir>

QProject::QProject():
    QObject(NULL),
    m_projectHost(NULL),
    m_projectStatus(PS_CLOSED),
    m_projectModified(PM_NOT_MODIFIED),
    m_languageManager(NULL),
    m_dataManager(NULL),
    m_styleSheetManager(NULL)
{
}

QProject::~QProject()
{
    close();
}

bool QProject::open(const QString &proFileName)
{

    setProjectStatus(PS_OPENING);

    QFile f(proFileName);
    if(!f.open(QFile::ReadOnly))
    {
        setProjectStatus(PS_CLOSED);
        return false;
    }

    QString buffer = f.readAll();
    f.close();

    XmlNode xml;

    if(!xml.load(buffer))
    {
        setProjectStatus(PS_CLOSED);
        return false;
    }

    m_projectHost = new QProjectHost;
    m_projectHost->setProperty("hostType","Project");
    m_projectHost->init();
    m_projectHost->fromXml(&xml);


    QString path = proFileName.left(proFileName.lastIndexOf("/"));
    m_projectHost->setPropertyValue("path",path);

    loadPages(path+"/pages");

    m_languageManager = new QLanguageManager(this);
    m_languageManager->load(path+"/languages");
    connect(m_languageManager,SIGNAL(currentLanguageChanged(QString)),
            this,SLOT(languageChanged()));

    m_dataManager = new QDataManager(this);
    m_dataManager->load(path);

    m_styleSheetManager = new QStyleSheetManager(this);
    m_styleSheetManager->load(path+"/stylesheet");

    setProjectStatus(PS_OPENED);
    setModified(PM_NOT_MODIFIED);
    emit projectOpened();
    return true;
}

void QProject::close()
{
    if(m_projectStatus == PS_OPENED)
    {
        setProjectStatus(PS_CLOSED);
        emit projectClosed();
    }
    setProjectStatus(PS_CLOSED);
    setModified(PM_NOT_MODIFIED);

    qDeleteAll(m_forms);
    m_forms.clear();

    if(m_projectHost != NULL)
    {
        delete m_projectHost;
        m_projectHost = NULL;
    }
    if(m_languageManager != NULL)
    {
        delete m_languageManager;
        m_languageManager = NULL;
    }

    if(m_dataManager != NULL)
    {
        delete m_dataManager;
        m_dataManager = NULL;
    }

    if(m_styleSheetManager != NULL)
    {
        delete m_styleSheetManager;
        m_styleSheetManager = NULL;
    }
}

QProjectHost* QProject::getProjectHost()
{
    return m_projectHost;
}

void QProject::setProjectStatus(enProjectStatus newStatus)
{
    if(m_projectStatus != newStatus)
    {
        m_projectStatus = newStatus;
        emit projectStatusChanged(m_projectStatus);
    }
}

enProjectStatus QProject::getProjectStatus()
{
    return m_projectStatus;
}

void QProject::addForm(QAbstractWidgetHost *host, int index)
{
    if(m_forms.contains(host))
    {
        return;
    }
    if(index < 0 || index > m_forms.size())
    {
        index = m_forms.size();
    }
    m_forms.insert(index,host);
    connect(host,SIGNAL(needUpdate(QStringProperty*)),
            this,SLOT(updateStringProperty(QStringProperty*)));
    emit hostAdded(host,index);
}

void QProject::loadPages(const QString &path)
{
    QFile file(path+"/page.list");

    if(!file.exists())
    {
        return;
    }

    if(!file.open(QFile::ReadOnly))
    {
        return;
    }

    XmlNode node;
    if(!node.load(file.readAll()))
    {
        return;
    }

    if(node.getTitle() != "Pages")
    {
        return;
    }

    foreach(XmlNode* p,node.getChildren())
    {
        if(p->getTitle() == "Page")
        {
            QString fileName = path + "/" + p->getText();
            QFile f(fileName);
            if(f.exists() && f.open(QFile::ReadOnly))
            {
                XmlNode xml;
                if(xml.load(f.readAll()))
                {
                    QAbstractHost * host = QHostFactory::createHost(
                                xml.getProperty("type"));
                    if(host != NULL)
                    {
                        host->fromXml(&xml);
                        host->setProperty("fileName",p->getText());
                        if(host->getUuid() == "")
                        {
                            host->setUuid(QUuid::createUuid().toString());
                        }
                        connect(host,SIGNAL(needUpdate(QStringProperty*)),
                                this,SLOT(updateStringProperty(QStringProperty*)));
                        m_forms.append((QAbstractWidgetHost*)host);
                    }
                }
            }
        }
    }
}

QList<QAbstractWidgetHost*> QProject::getForms()
{
    return m_forms;
}

void QProject::setModified(enProjectModified modified)
{
    if(m_projectModified != modified)
    {
        m_projectModified = modified;
        emit modifiedChanged();
    }
}

enProjectModified QProject::getProjectModified()
{
    return m_projectModified;
}

QAbstractHost * QProject::getHostByUuid(const QString &uuid)
{
    QList<QAbstractHost*> list;

    foreach(QAbstractWidgetHost * h,m_forms)
    {
        list.append((QAbstractHost*)h);
    }

    while(list.size()>0)
    {
        QAbstractHost * host = list.takeFirst();
        if(host->getUuid() == uuid)
        {
            return host;
        }
        list += host->getChildrenHost();
    }

    return NULL;
}

QLanguageManager* QProject::getLanguageManager()
{
    return m_languageManager;
}

QDataManager* QProject::getDataManager()
{
    return m_dataManager;
}

QStyleSheetManager* QProject::getStyleSheetManager()
{
    return m_styleSheetManager;
}

bool QProject::save()
{
    if(m_projectStatus ==PS_OPENED)
    {
        QString path = m_projectHost->getPropertyValue("path").toString();
        if(!m_projectHost->save(path+"/project.pfl"))
        {
            return false;
        }
        m_languageManager->save(path+"/languages");
        m_dataManager->save(path);
        m_styleSheetManager->save(path+"/stylesheet");

        foreach(QAbstractHost *host,m_forms)
        {
            XmlNode xml;
            if(!host->toXml(&xml))
            {
                return false;
            }
            QString buffer;
            if(!xml.save(buffer))
            {
                return false;
            }
            QString fileName = host->property("fileName").toString();
            if(fileName == "")
            {
                fileName = host->getPropertyValue("objectName").toString()
                        +".pg";
            }
            QFile f(path+"/pages/"+fileName);
            if(!f.open(QFile::ReadWrite))
            {
                return false;
            }
            f.write(buffer.toLocal8Bit());
            f.close();
        }
    }
    return true;
}

void QProject::updateStringProperty(QStringProperty *pro)
{
    if(!pro->getTranslation())
    {
        return;
    }
    QLanguage * language = m_languageManager->getCurrentLanguage();

    if(language != NULL)
    {
        pro->setValue(language->getValue(pro->getUuid()));
    }
    else
    {
        QLanguageItem * item = m_languageManager->getItem(pro->getUuid());
        if(item != NULL)
        {
            pro->setValue(item->m_name);
        }
        else
        {
            pro->setValue("");
        }
    }
}

void QProject::languageChanged()
{
    m_projectHost->updateStringProperty();

    foreach(QAbstractWidgetHost * host,m_forms)
    {
        host->updateStringProperty();
    }
}
