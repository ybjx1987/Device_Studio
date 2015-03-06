#include "qstylesheetgrouplistview.h"

#include "../../../libs/kernel/stylesheet/qstylesheetmanager.h"
#include "../../../libs/kernel/stylesheet/qstylesheetgroup.h"

#include <QHeaderView>

QStyleSheetGroupListView::QStyleSheetGroupListView(QWidget * parent):
    QBaseListView(parent)
{
    header()->hide();
    connect(this,SIGNAL(itemSelectionChanged()),
            this,SLOT(select()));
}

void QStyleSheetGroupListView::init(QStyleSheetManager *manager)
{
    clear();
    QList<QStyleSheetGroup*> groups = manager->getGroups();

    foreach(QStyleSheetGroup * g,groups)
    {
        QTreeWidgetItem * item = new QTreeWidgetItem(this);
        item->setText(0,g->getName());
        item->setToolTip(0,g->getName());
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        m_itemToGroup.insert(item,g);
        m_groupToItem.insert(g,item);
    }

    if(groups.size() >0)
    {
        m_groupToItem.value(groups.first())->setSelected(true);
    }
}

void QStyleSheetGroupListView::clear()
{
    m_itemToGroup.clear();
    m_groupToItem.clear();
    QBaseListView::clear();
}

void QStyleSheetGroupListView::select()
{
    QList<QTreeWidgetItem*> list = selectedItems();
    if(list.size() > 0)
    {
        emit groupSelect(m_itemToGroup.value(list.first()));
    }
    else
    {
        emit groupSelect(NULL);
    }
}

void QStyleSheetGroupListView::groupAdded(QStyleSheetGroup *group)
{
    QTreeWidgetItem * item = new QTreeWidgetItem(this);
    item->setText(0,group->getName());
    item->setToolTip(0,group->getName());
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    m_itemToGroup.insert(item,group);
    m_groupToItem.insert(group,item);

    emit updateAction();

    if(m_itemToGroup.size() == 1)
    {
        item->setSelected(true);
    }
}

void QStyleSheetGroupListView::groupDeled(QStyleSheetGroup *group)
{
    QTreeWidgetItem * item = m_groupToItem.value(group);
    m_groupToItem.remove(group);
    m_itemToGroup.remove(item);
    delete item;
    emit updateAction();
}
