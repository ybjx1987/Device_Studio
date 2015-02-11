#include "qproject.h"

#include "host/qprojecthost.h"

#include "../kernel/xmlnode.h"

#include <QFile>

QProject::QProject():
    QObject(NULL),
    m_projectHost(NULL),
    m_projectStatus(PS_CLOSED)
{

}

QProject::~QProject()
{

}

bool QProject::open(const QString &proFileName)
{
    close();

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
    m_projectHost->init();
    m_projectHost->fromXml(&xml);


    emit projectOpened();
    setProjectStatus(PS_OPENED);
    return true;
}

void QProject::close()
{
    if(m_projectHost != NULL)
    {
        delete m_projectHost;
        m_projectHost = NULL;
        emit projectClosed();
    }
    setProjectStatus(PS_CLOSED);
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

    emit hostAdded(host,index);
}
