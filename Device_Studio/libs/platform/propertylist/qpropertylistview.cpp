#include "qpropertylistview.h"

#include "qpropertyeditorpane.h"

#include "../stylehelper.h"
#include "../../kernel/property/qabstractproperty.h"

#include <QHeaderView>
#include <QMouseEvent>

QWidget * QPropertyListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget* wid = NULL;
    if(index.column() ==1)
    {
        QTreeWidgetItem *item = m_listView->itemFromIndex(index);
        QAbstractProperty *property = m_listView->m_itemToProperty.value(item);
        if(property != NULL && property->getVisible() && property->getEditable())
        {
            wid = new QPropertyEditorPane(property,parent);
        }
    }
    return wid;
}

void QPropertyListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect.adjusted(0,0,0,-1));
}

QPropertyListView::QPropertyListView(QWidget* parent):
    QBaseListView(parent)
{
    setFrameStyle(QFrame::NoFrame);
    setIconSize(QSize(18,18));
    setColumnCount(2);
    setHeaderLabels(QStringList()<<tr("Property")<<tr("Value"));
    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::EditKeyPressed);
    setRootIsDecorated(false);

    setItemDelegate(new QPropertyListDelegate(this));

    m_expandIcon = StyleHelper::drawIndicatorIcon(palette(),style());

    QPalette p = this->palette();
    p.setColor(QPalette::Inactive,QPalette::Highlight,
               p.color(QPalette::Active,QPalette::Highlight));
    p.setColor(QPalette::Inactive,QPalette::HighlightedText,
               p.color(QPalette::Active,QPalette::HighlightedText));
    setPalette(p);
}

void QPropertyListView::setPropertys(const QList<QAbstractProperty *> &propertys)
{
    clear();
    m_propertys = propertys;
    updateView();
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
}

void QPropertyListView::mousePressEvent(QMouseEvent *event)
{
    QTreeWidget::mousePressEvent(event);

    QTreeWidgetItem *item = itemAt(event->pos());
    if(item != NULL)
    {
        if(m_groupToItem.values().contains(item))
        {
            if(event->pos().x()+header()->offset()<20)
            {
                item->setExpanded(!item->isExpanded());
            }
        }
        else
        {
            if(header()->logicalIndexAt(event->pos()) == 1
                    && event->button() == Qt::LeftButton)
            {
                editItem(item,1);
            }
        }
    }
}
