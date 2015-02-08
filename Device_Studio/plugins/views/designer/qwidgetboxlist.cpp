#include "qwidgetboxlist.h"

#include "qdesignerdnditem.h"

#include "../../../libs/platform/stylehelper.h"
#include "../../../libs/kernel/host/qhostfactory.h"
#include "../../../libs/kernel/host/qwidgethost.h"
#include "../../../libs/platform/qbaseitemdelegate.h"

#include <QHeaderView>

static bool checkHost(QWidgetHostInfo * info1,QWidgetHostInfo * info2)
{
    return info1->m_index < info2->m_index;
}

QWidgetBoxList::QWidgetBoxList(QWidget* parent ):
    QBaseListView(parent)
{
    setColumnCount(1);
    header()->hide();

    initWidgetBox();
}

void QWidgetBoxList::initWidgetBox()
{
    QList<QAbstractHostInfo*> list = QHostFactory::getHostInfo();
    QList<QWidgetHostInfo*> widgetList;

    foreach(QAbstractHostInfo * info,list)
    {
        if(info->m_type == "Widget")
        {
            widgetList.append((QWidgetHostInfo*)info);
        }
    }

    qSort(widgetList.begin(),widgetList.end(),checkHost);

    foreach(QWidgetHostInfo * info,widgetList)
    {
        addWidget(info);
    }

    this->expandAll();
}

void QWidgetBoxList::addWidget(QWidgetHostInfo *info)
{
    if(info == NULL || info->m_showGroup ==""
            || info->m_showName == "")
    {
        return;
    }

    QTreeWidgetItem *p = m_nameToGroup.value(info->m_showGroup);
    QTreeWidgetItem *item;
    if(p == NULL)
    {
        p = new QTreeWidgetItem(this);
        p->setText(0,info->m_showGroup);
        p->setFlags(Qt::ItemIsEnabled);
        p->setIcon(0,m_expandIcon);
        m_nameToGroup.insert(info->m_showGroup,p);
        p->setData(0,DarkRole,true);
    }

    item = new QTreeWidgetItem(p);
    item->setText(0,info->m_showName);
    item->setIcon(0,QIcon(info->m_showIcon));
    item->setFlags(Qt::ItemIsEnabled);
    item->setData(0,DarkRole,false);
    m_infoToItem.insert(info,item);
    m_itemToInfo.insert(item,info);
}

void QWidgetBoxList::clickEditItem(QTreeWidgetItem * item,int index)
{

    if(m_itemToInfo.keys().contains(item))
    {
        //if(event->button()!=Qt::LeftButton)
        //{
        //    return;
        //}
        QWidgetHostInfo *info=m_itemToInfo.value(item);
        if(info!=NULL)
        {
            handleMousePress(info);
        }
    }
}

void QWidgetBoxList::handleMousePress(QWidgetHostInfo *info)
{
    QList<QDesignerDnDItemInterface*> item_list;
    item_list.append(new WidgetBoxDnDItem(info->m_name,QCursor::pos()));

    foreach(QDesignerDnDItemInterface *item,item_list)
    {
        if(item->host()==NULL)
        {
            return;
        }
    }

    QDesignerMimeData::execDrag(item_list,this);
}
