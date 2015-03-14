#include "qstylesheetsync.h"

#include "host/qabstractwidgethost.h"
#include "stylesheet/qstylesheetmanager.h"
#include "stylesheet/qstylesheetgroup.h"
#include "stylesheet/qstylesheetitem.h"
#include "stylesheet/qstylesheetitemtitle.h"

#include <QWidget>
#include <QVariant>

QStyleSheetSync::QStyleSheetSync(QStyleSheetManager *manager,
                                 const QList<QAbstractWidgetHost*> &forms,
                                 QObject *parent) :
    QObject(parent),
    m_styleSheetManager(manager)
{
    foreach(QAbstractWidgetHost * form,forms)
    {
        m_forms.append(form);
        updateStyleSheet(form);
    }

    connect(m_styleSheetManager,SIGNAL(needUpdateStyleSheet(QList<QStyleSheetItem*>)),
            this,SLOT(needUpdateStyleSheet(QList<QStyleSheetItem*>)));
}

QStyleSheetSync::~QStyleSheetSync()
{

}

void QStyleSheetSync::addForm(QAbstractHost *form)
{
    m_forms.append(form);
    updateStyleSheet(form);
}

void QStyleSheetSync::delForm(QAbstractHost *form)
{
    m_forms.removeAll(form);
}

QList<QAbstractHost*> QStyleSheetSync::getWidgetByType(const QString &type)
{
    QList<QAbstractHost*> ret;
    QList<QAbstractHost*> list;

    foreach(QAbstractHost * form,m_forms)
    {
        list.clear();
        list.append(form);
        while(list.size()>0)
        {
            QAbstractHost * host = list.takeFirst();
            if(host->property("hostName").toString() == type)
            {
                ret.append(form);
            }
            if(host->getChildrenHost().size() == 0)
            {
                list += host->getChildrenHost();
            }
            else
            {
                QObjectList objList = host->children();
                while(objList.size()>0)
                {
                    QWidget * wid = (QWidget*)objList.takeFirst();
                    if(wid->metaObject()->className() == type)
                    {
                        ret.append(form);
                    }
                    objList+=wid->children();
                }
            }
        }
    }

    return ret;
}

QList<QAbstractHost*> QStyleSheetSync::getWidgetByName(const QString &name)
{
    QList<QAbstractHost*> ret;
    QList<QAbstractHost*> list = m_forms;

    while(list.size()>0)
    {
        QAbstractHost * host = list.takeFirst();
        if(host->getPropertyValue("objectName").toString() == name)
        {
            ret.append(host);
        }
        else
        {
            if(host->getChildrenHost().size()>0)
            {
                list += host->getChildrenHost();
            }
            else
            {
                QObjectList objList;
                objList.append(host->getObject());

                while(objList.size()>0)
                {
                    QWidget * wid = (QWidget*)objList.takeFirst();

                    if(wid->objectName() == name)
                    {
                        ret.append(host);
                    }
                    objList += wid->children();
                }
            }
        }
    }

    return ret;
}

QList<QStyleSheetItem*> QStyleSheetSync::getItemByType(const QString &type)
{
    QList<QStyleSheetItem*> list;
    foreach(QStyleSheetGroup * group , m_styleSheetManager->getGroups())
    {
        foreach(QStyleSheetItem * item,group->getItems())
        {
            foreach(QStyleSheetItemTitle * title,item->getTitles())
            {
                if(title->getType() == "By Type"
                        && title->getName() == type)
                {
                    list.append(item);
                    break;
                }
            }
        }
    }

    return list;
}

QList<QStyleSheetItem*> QStyleSheetSync::getItemByName(const QString &name)
{
    QList<QStyleSheetItem*> list;
    foreach(QStyleSheetGroup * group , m_styleSheetManager->getGroups())
    {
        foreach(QStyleSheetItem * item,group->getItems())
        {
            foreach(QStyleSheetItemTitle * title,item->getTitles())
            {
                if(title->getType() == "By Name"
                        && title->getName() == name)
                {
                    list.append(item);
                    break;
                }
            }
        }
    }

    return list;
}

void QStyleSheetSync::updateStyleSheet(QAbstractHost *host)
{
    QList<QStyleSheetItem*> list;
    QString styleSheet;
    if(host->getParent() == NULL)
    {
        list += getItemByType(host->property("hostName").toString());
        foreach(QStyleSheetItem * item,list)
        {
            styleSheet += item->getStyleSheet(host->property("hostName").toString());
        }
    }

    list = getItemByName(host->getPropertyValue("objectName").toString());

    foreach(QStyleSheetItem *item,list)
    {
        styleSheet += item->getStyleSheet("#"+host->getPropertyValue("objectName").toString());
    }
    qDebug(styleSheet.toLocal8Bit());
    host->getObject()->setProperty("styleSheet",styleSheet);

    if(host->getChildrenHost().size()>0)
    {
        foreach(QAbstractHost * h,host->getChildrenHost())
        {
            updateStyleSheet(h);
        }
    }
    else
    {
        QObjectList objList = host->getObject()->children();
        while(objList.size()>0)
        {
            QObject * obj = objList.takeFirst();
            if(!obj->isWidgetType())
            {
                continue;
            }
            if(obj->objectName() == "")
            {
                continue;
            }
            list.clear();
            list = getItemByName(obj->objectName());
            styleSheet = "";
            foreach(QStyleSheetItem *item,list)
            {
                styleSheet += item->getStyleSheet("#"+obj->objectName());
            }
            obj->setProperty("styleSheet",styleSheet);
            objList += obj->children();
        }
    }
}

void QStyleSheetSync::needUpdateStyleSheet(const QList<QStyleSheetItem *> &items)
{
    QList<QAbstractHost*> list;
    QList<QAbstractHost*> temp;
    foreach(QStyleSheetItem * item,items)
    {
        foreach(QStyleSheetItemTitle * title,item->getTitles())
        {
            if(title->getType() == "By Name")
            {
                temp += getWidgetByName(title->getName());
            }
            else
            {
                temp += getWidgetByType(title->getName());
            }
        }
    }

    while(temp.size() > 0)
    {
        QAbstractHost * h = temp.takeFirst();
        QAbstractHost * host = h;
        while(h != NULL)
        {
            if(list.contains(h) || temp.contains(h))
            {
                break;
            }
            else
            {
                h = h->getParent();
            }
        }
        if(h == NULL)
        {
            list.append(host);
        }
    }

    foreach(QAbstractHost * host,list)
    {
        updateStyleSheet(host);
    }
}
