#include "qdatalistview.h"

#include "../../../libs/kernel/data/qdatamanager.h"
#include "../../../libs/kernel/data/qdatagroup.h"
#include "../../../libs/kernel/data/qabstractdatahost.h"
#include "../../../libs/platform/qbaseitemdelegate.h"
#include "../../../libs/kernel/property/qabstractproperty.h"

#include <QStringList>

QDataListView::QDataListView(QWidget* parent):
    QBaseListView(parent)
{
    setHeaderLabels(QStringList()<<tr("Name")<<tr("Value")<<tr("NeedSave")
                    <<tr("Type")<<tr("Explanation"));
    connect(this,SIGNAL(itemSelectionChanged()),this,
            SLOT(dataSelect()));
}

void QDataListView::clear()
{
    qDeleteAll(m_itemToData.keys());
    qDeleteAll(m_itemToGroup.keys());
    m_itemToData.clear();
    m_itemToGroup.clear();
    m_dataToItem.clear();
    m_groupToItem.clear();
    m_dataManager = NULL;
}

void QDataListView::setDataManager(QDataManager *manager)
{
    clear();
    m_dataManager = manager;

    QList<QDataGroup*>  groups = m_dataManager->getGroups();

    connect(manager,SIGNAL(groupAdded(QDataGroup*,int)),
            this,SLOT(groupAdded(QDataGroup*,int)));
    connect(manager,SIGNAL(groupDeled(QDataGroup*)),
            this,SLOT(groupDeled(QDataGroup*)));

    foreach(QDataGroup * g,groups)
    {
        addGroup(g);
    }
}

void QDataListView::addGroup(QDataGroup *group,int index)
{
    if(index <0 || index > topLevelItemCount())
    {
        index = topLevelItemCount();
    }
    QTreeWidgetItem * item = new QTreeWidgetItem;
    item->setText(0,group->getGroupName());
    item->setToolTip(0,group->getGroupName());
    for(int i= 0;i<5;i++)
    {
        item->setData(i,DarkRole,true);
    }
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->insertTopLevelItem(index,item);
    item->setExpanded(true);
    m_itemToGroup.insert(item,group);
    m_groupToItem.insert(group,item);

    connect(group,SIGNAL(dataAdded(QAbstractDataHost*,int)),
            this,SLOT(dataAdded(QAbstractDataHost*,int)));
    connect(group,SIGNAL(dataDeled(QAbstractDataHost*)),
            this,SLOT(dataDeled(QAbstractDataHost*)));


    QList<QAbstractDataHost*> datas = group->getDatas();

    foreach(QAbstractDataHost * d,datas)
    {
        addData(group,d);
    }
}

void QDataListView::addData(QDataGroup* group,QAbstractDataHost *data,int index)
{
    QTreeWidgetItem * parentItem = m_groupToItem.value(group);

    if(parentItem == NULL)
    {
        return;
    }

    if(index <0 || index > parentItem->childCount())
    {
        index = parentItem->childCount();
    }

    QTreeWidgetItem * item = new QTreeWidgetItem;
    parentItem->insertChild(index,item);

    QAbstractProperty * pro;

    QStringList list;
    list<<"objectName"<<"value"<<"needSave"<<"type"<<"explanation";

    for(int i = 0;i<list.size();i++)
    {
        pro = data->getProperty(list.at(i));
        item->setText(i,pro->getValueText());
        item->setToolTip(i,pro->getValueText());
    }

    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    m_dataToItem.insert(data,item);
    m_itemToData.insert(item,data);
}

void QDataListView::groupAdded(QDataGroup *group, int index)
{
    if(m_groupToItem.keys().contains(group))
    {
        return;
    }
    addGroup(group,index);
    emit updateAction();
}

void QDataListView::groupDeled(QDataGroup *group)
{
    if(!m_groupToItem.keys().contains(group))
    {
        return;
    }

    QList<QAbstractDataHost*> list = group->getDatas();

    foreach(QAbstractDataHost * data,list)
    {
        QTreeWidgetItem * item = m_dataToItem.value(data);
        m_dataToItem.remove(data);
        m_itemToData.remove(item);
        delete item;
    }

    QTreeWidgetItem * item = m_groupToItem.value(group);

    m_groupToItem.remove(group);
    m_itemToGroup.remove(item);

    delete item;
    emit updateAction();
}

void QDataListView::dataAdded(QAbstractDataHost *data, int index)
{
    QDataGroup * group = (QDataGroup*)sender();

    if(m_dataToItem.keys().contains(data)
            || !m_groupToItem.keys().contains(group))
    {
        return;
    }

    addData(group,data,index);
    emit updateAction();
}

void QDataListView::dataDeled(QAbstractDataHost *data)
{
    if(!m_dataToItem.keys().contains(data))
    {
        return;
    }
    QTreeWidgetItem * item = m_dataToItem.value(data);

    m_dataToItem.remove(data);
    m_itemToData.remove(item);

    delete item;
    emit updateAction();
}

void QDataListView::dataSelect()
{
    QList<QTreeWidgetItem*> list = selectedItems();
    if(list.size() == 0)
    {
        emit dataSelected(NULL);
        return;
    }
    QTreeWidgetItem * item = list.first();

    if(m_itemToData.keys().contains(item))
    {
        emit dataSelected(m_itemToData.value(item));
    }
    else
    {
        emit dataSelected(NULL);
    }
}
