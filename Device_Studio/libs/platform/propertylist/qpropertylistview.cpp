#include "qpropertylistview.h"

#include "qpropertyeditorpane.h"

#include "../stylehelper.h"
#include "../../kernel/property/qabstractproperty.h"
#include "../undocommand/qpropertyeditundocommand.h"

#include <QHeaderView>
#include <QMouseEvent>
#include <QList>

QWidget * QPropertyListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPropertyEditorPane* wid = NULL;
    if(index.column() ==1)
    {
        QTreeWidgetItem *item = m_listView->itemFromIndex(index);
        QAbstractProperty *property = m_listView->m_itemToProperty.value(item);
        if(property != NULL && property->getVisible() && property->getEditable())
        {
            wid = new QPropertyEditorPane(property,parent);
            connect(wid,SIGNAL(propertyValueEdit(QAbstractProperty*,QVariant)),
                    m_listView,SLOT(propertyValueEdit(QAbstractProperty*,QVariant)));
        }
    }
    return wid;
}

void QPropertyListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect.adjusted(0,0,0,-1));
}

void QPropertyListDelegate::setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const
{
}

QPropertyListView::QPropertyListView(QWidget* parent):
    QBaseListView(parent),
    m_undoStack(NULL)
{
    setColumnCount(2);
    setHeaderLabels(QStringList()<<tr("Property")<<tr("Value"));

    setItemDelegate(new QPropertyListDelegate(this));

    m_expandIcon = StyleHelper::drawIndicatorIcon(palette(),style());
}

void QPropertyListView::setPropertys(const QList<QAbstractProperty *> &propertys,
                                     QUndoStack* undoStack)
{
    clear();
    QList<QAbstractProperty*> list = m_propertys;
    while(list.size()>0)
    {
        QAbstractProperty * pro = list.takeFirst();
        disconnect(pro,SIGNAL(valueChanged(QVariant,QVariant)),this,
                   SLOT(propertyValueChanged()));
        list +=pro->getChildren();
    }

    m_propertys = propertys;
    list = m_propertys;
    while(list.size()>0)
    {
        QAbstractProperty * pro = list.takeFirst();
        connect(pro,SIGNAL(valueChanged(QVariant,QVariant)),this,
                   SLOT(propertyValueChanged()));
        list +=pro->getChildren();
    }
    updateView();

    m_undoStack = undoStack;
}

void QPropertyListView::updateView()
{
    foreach(QAbstractProperty * pro,m_propertys)
    {
        insertItem(pro);
    }
}

void QPropertyListView::insertItem(QAbstractProperty *property,
                                   QAbstractProperty *parent)
{
    if(property == NULL)
    {
        return;
    }

    if(!property->getVisible())
    {
        return;
    }

    QTreeWidgetItem * parentItem;
    if(parent == NULL)
    {
        QString str = property->getGroup();
        if(str == "")
        {
            str = tr("Common");
        }
        parentItem = m_groupToItem.value(str);
        if(parentItem == NULL)
        {
            parentItem = new QTreeWidgetItem(this);
            parentItem->setText(0,str);
            parentItem->setIcon(0,m_expandIcon);
            parentItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            m_groupToItem.insert(str,parentItem);
            m_groups.append(parentItem);
            parentItem->setExpanded(true);
            parentItem->setData(0,DarkRole,true);
            parentItem->setData(1,DarkRole,true);
        }
    }
    else
    {
        parentItem = m_propertyToItem.value(parent);
    }
    if(parentItem == NULL)
    {
        return;
    }

    QTreeWidgetItem *item = new QTreeWidgetItem(parentItem);
    item->setText(0,property->getShowName());
    item->setToolTip(0,property->getShowName());
    item->setText(1,property->getValueText());
    item->setToolTip(1,property->getValueText());
    item->setIcon(1,property->getValueIcon());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    item->setExpanded(property->getNeedExpanded());

    m_itemToProperty.insert(item,property);
    m_propertyToItem.insert(property,item);

    foreach(QAbstractProperty * pro,property->getChildren())
    {
        insertItem(pro,property);
    }
}

void QPropertyListView::clear()
{
    QMapIterator<QAbstractProperty*,QTreeWidgetItem*> it(m_propertyToItem);
    while(it.hasNext())
    {
        it.next();
        it.key()->setNeedExpanded(it.value()->isExpanded());
    }
    QBaseListView::clear();

    m_groupToItem.clear();
    m_propertys.clear();
    m_propertyToItem.clear();
    m_itemToProperty.clear();
    m_groups.clear();
    m_undoStack = NULL;
}

void QPropertyListView::clickEditItem(QTreeWidgetItem* item,int index)
{
    if(index == 1)
    {
        editItem(item,1);
    }
}

void QPropertyListView::propertyValueChanged()
{
    QAbstractProperty* pro =(QAbstractProperty*)sender();
    QTreeWidgetItem * item = m_propertyToItem.value(pro);
    item->setText(1,pro->getValueText());
    item->setToolTip(1,pro->getValueText());
    item->setIcon(1,pro->getValueIcon());
}

void QPropertyListView::propertyValueEdit(QAbstractProperty *property, const QVariant &value)
{
    QAbstractProperty * pro = property;
    QString str = pro->getName();
    while(pro->getParent() != NULL)
    {
        pro = pro->getParent();
        str = pro->getName()+"."+str;
    }
    if(m_undoStack != NULL && m_propertys.contains(pro))
    {
        QPropertyEditUndoCommand *cmd = new QPropertyEditUndoCommand(
                    property->getHostUuid(),
                    str,
                    value,
                    property->getValue());
        m_undoStack->push(cmd);
    }
}
