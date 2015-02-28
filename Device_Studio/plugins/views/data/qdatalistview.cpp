#include "qdatalistview.h"

#include "../../../libs/kernel/data/qdatamanager.h"
#include "../../../libs/kernel/data/qdatagroup.h"
#include "../../../libs/kernel/data/qabstractdatahost.h"
#include "../../../libs/platform/qbaseitemdelegate.h"
#include "../../../libs/kernel/property/qabstractproperty.h"
#include "../../../libs/platform/qvalidatoredit.h"
#include "../../../libs/platform/propertylist/qpropertyeditorpane.h"
#include "../../../libs/platform/qbuttonlineedit.h"

#include <QStringList>

QWidget * QDataItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    QWidget * wid = NULL;

    QTreeWidgetItem * item = m_listView->itemFromIndex(index);

    if(m_listView->m_itemToData.keys().contains(item))
    {
        int count = index.column();

        switch(count)
        {
        case 0:
        {
            QValidatorEdit *edit = new QValidatorEdit("[_a-zA-z][_a-zA-Z0-9]{,64}",parent);
            QDataGroup *group = m_listView->m_itemToGroup.value(item->parent());
            QStringList list;
            foreach(QAbstractDataHost * host,group->getDatas())
            {
                list.append(host->getPropertyValue("objectName").toString());
            }
            list.removeAll(m_listView->m_itemToData.value(item)
                           ->getPropertyValue("objectName").toString());
            edit->setIntermediateList(list);
            wid = edit;
        }
            break;
        case 1:
        {
            QAbstractDataHost * data = m_listView->m_itemToData.value(item);
            QAbstractProperty * pro = data->getProperty("value");
            QPropertyEditorPane * panel = new QPropertyEditorPane(pro,parent);

            connect(panel,SIGNAL(propertyValueEdit(QAbstractProperty*,QVariant)),
                    m_listView,SLOT(propertyValueEdit(QAbstractProperty*,QVariant)));

            wid = panel;
        }
            break;
        case 4:
        {
            wid = new QButtonLineEdit(parent);
        }
            break;
        default:
            break;
        }
    }
    else
    {
        if(index.column() == 0)
        {
            QValidatorEdit *edit = new QValidatorEdit("[_a-zA-z][_a-zA-Z0-9]{,64}",parent);
            QStringList list;
            foreach(QDataGroup * group,m_listView->m_groupToItem.keys())
            {
                list.append(group->getGroupName());
            }
            list.removeAll(m_listView->m_itemToGroup.value(item)
                           ->getGroupName());
            edit->setIntermediateList(list);
            wid = edit;
        }
    }

    return wid;
}

void QDataItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *, const QModelIndex &index) const
{
    QTreeWidgetItem * item = m_listView->itemFromIndex(index);

    if(m_listView->m_itemToData.keys().contains(item))
    {
        QAbstractDataHost * data = m_listView->m_itemToData.value(item);

        int count = index.column();

        switch(count)
        {
        case 0:
        {
            QValidatorEdit *e = (QValidatorEdit*)editor;
            if(e->value() != "")
            {
                data->setPropertyValue("objectName",e->value());
            }
        }
            break;
        case 4:
        {
            QButtonLineEdit *e=(QButtonLineEdit*)editor;
            data->setPropertyValue("explanation",e->text());
        }
        default:
            break;
        }
    }
    else
    {
        QDataGroup * group = m_listView->m_itemToGroup.value(item);
        if(index.column() == 0)
        {
            QValidatorEdit *e = (QValidatorEdit*)editor;
            if(e->value() != "")
            {
                group->setGroupName(e->value());
            }
        }
    }
}

QDataListView::QDataListView(QWidget* parent):
    QBaseListView(parent)
{
    setHeaderLabels(QStringList()<<tr("Name")<<tr("Value")<<tr("NeedSave")
                    <<tr("Type")<<tr("Explanation"));
    connect(this,SIGNAL(itemSelectionChanged()),this,
            SLOT(dataSelect()));
    setItemDelegate(new QDataItemDelegate(this));
    //setRootIsDecorated(true);
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this,SLOT(doubleItemClicked(QTreeWidgetItem*,int)));
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
    item->setIcon(0,m_expandIcon);
    for(int i= 0;i<5;i++)
    {
        item->setData(i,DarkRole,true);
    }
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->insertTopLevelItem(index,item);
    item->setExpanded(true);
    m_itemToGroup.insert(item,group);
    m_groupToItem.insert(group,item);

    connectGroup(group);

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
    connectDataHost(data);
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

    disconnectGroup(group);

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
    disconnectDataHost(data);
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

void QDataListView::clickEditItem(QTreeWidgetItem *item, int index)
{
    editItem(item,index);
}

void QDataListView::connectDataHost(QAbstractDataHost *data)
{
    QStringList list;
    list<<"objectName"<<"value"<<"needSave"<<"explanation";
    foreach(QString str,list)
    {
        QAbstractProperty * pro = data->getProperty(str);

        connect(pro,SIGNAL(valueChanged(QVariant,QVariant)),
                this,SLOT(dataPropertyChanged()));
    }
}

void QDataListView::disconnectDataHost(QAbstractDataHost *data)
{
    QStringList list;
    list<<"objectName"<<"value"<<"needSave"<<"explanation";
    foreach(QString str,list)
    {
        QAbstractProperty * pro = data->getProperty(str);

        disconnect(pro,SIGNAL(valueChanged(QVariant,QVariant)),
                this,SLOT(dataPropertyChanged()));
    }
}

void QDataListView::dataPropertyChanged()
{
    QAbstractProperty * pro = (QAbstractProperty*)sender();
    QAbstractDataHost * data;
    data = m_dataManager->getDataByUuid(pro->getHostUuid());
    QTreeWidgetItem * item = NULL;
    if(data != NULL)
    {
        item = m_dataToItem.value(data);
    }
    if(item == NULL)
    {
        return;
    }

    QStringList list;
    list<<"objectName"<<"value"<<"needSave"<<""<<"explanation";

    if(list.contains(pro->getName()))
    {
        item->setText(list.indexOf(pro->getName()),pro->getValueText());
        item->setToolTip(list.indexOf(pro->getName()),pro->getValueText());
    }
}

void QDataListView::connectGroup(QDataGroup *group)
{
    connect(group,SIGNAL(groupNameChanged()),
            this,SLOT(groupNameChanged()));
    connect(group,SIGNAL(dataAdded(QAbstractDataHost*,int)),
            this,SLOT(dataAdded(QAbstractDataHost*,int)));
    connect(group,SIGNAL(dataDeled(QAbstractDataHost*)),
            this,SLOT(dataDeled(QAbstractDataHost*)));
}

void QDataListView::disconnectGroup(QDataGroup *group)
{
    disconnect(group,SIGNAL(groupNameChanged()),
            this,SLOT(groupNameChanged()));
    disconnect(group,SIGNAL(dataAdded(QAbstractDataHost*,int)),
            this,SLOT(dataAdded(QAbstractDataHost*,int)));
    disconnect(group,SIGNAL(dataDeled(QAbstractDataHost*)),
            this,SLOT(dataDeled(QAbstractDataHost*)));
}

void QDataListView::groupNameChanged()
{
    QDataGroup * group = (QDataGroup*)sender();

    QTreeWidgetItem *item = m_groupToItem.value(group);

    if(item != NULL)
    {
        item->setText(0,group->getGroupName());
        item->setToolTip(0,group->getGroupName());
    }
}

void QDataListView::propertyValueEdit(QAbstractProperty* property,
                                      const QVariant & value)
{
    property->setValue(value);
}

void QDataListView::doubleItemClicked(QTreeWidgetItem *item, int index)
{
    if(m_dataToItem.values().contains(item) && index == 2)
    {
        QAbstractDataHost *data = m_itemToData.value(item);
        bool needSave = data->getPropertyValue("needSave").toBool();
        data->setPropertyValue("needSave",!needSave);
    }
}
