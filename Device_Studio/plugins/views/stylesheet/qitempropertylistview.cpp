#include "qitempropertylistview.h"

#include "../../../libs/platform/qbaseitemdelegate.h"
#include "../../../libs/kernel/stylesheet/qsheetpropertyfactory.h"
#include "../../../libs/kernel/stylesheet/type/qabstractsheettype.h"
#include "../../../libs/kernel/stylesheet/qstylesheetitem.h"

#include <QHeaderView>
#include <QComboBox>

class QItemPropertyDelegate: public QBaseItemDelegate
{
public:
    QItemPropertyDelegate(QItemPropertyListView* view):m_listView(view){}
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void    drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;

    void    setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
protected:
    QItemPropertyListView   *m_listView;
};

QWidget * QItemPropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    QWidget * wid = NULL;
    if(index.column() == 0)
    {
        QComboBox * comboBox = new QComboBox(parent);
        QStringList list = QSheetPropertyFactory::getPropertyInfo();
        list.insert(0,tr("Clear"));
        comboBox->addItems(list);
        comboBox->setCurrentIndex(1);
        wid = comboBox;
    }

    if(wid != NULL)
    {
        wid->setProperty("no-ManhattanStyle",true);
    }
    return wid;
}

void QItemPropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QTreeWidgetItem * item = m_listView->itemFromIndex(index);
        QComboBox * comboBox = (QComboBox *)editor;
        QString name = comboBox->currentText();
        if(name == tr("Clear"))
        {
            if(item != m_listView->m_emptyItem)
            {
                QAbstractSheetType * pro = m_listView->m_itemToProperty.value(item);
                if(pro != NULL)
                {
                    m_listView->m_sheetItem->delProperty(pro);
                }
            }
        }
        else
        {
            QAbstractSheetType * pro = m_listView->m_itemToProperty.value(item);
            if(pro != NULL && pro->getName() == name)
            {
                return;
            }
            QAbstractSheetType * newPro = QSheetPropertyFactory::createProperty(name);
            if(newPro != NULL)
            {
                if(item != m_listView->m_emptyItem)
                {
                    m_listView->m_sheetItem->replaceProperty(pro,newPro);
                }
                else
                {
                    m_listView->m_sheetItem->addProperty(newPro);
                }
            }
        }
    }
}

void QItemPropertyDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    QStyleOptionViewItem opt = option;
    if(rect.left()<10)
    {
        opt.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;
        QBaseItemDelegate::drawDisplay(painter,opt,rect.adjusted(0,0,-5,0),text);

    }
    else
    {
        opt.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
        QBaseItemDelegate::drawDisplay(painter,opt,rect,text);
    }
}

QItemPropertyListView::QItemPropertyListView(QStyleSheetItem * item,QWidget * parent ):
    QBaseListView(parent),
    m_sheetItem(item)
{
    header()->hide();
    setColumnCount(2);
    setColumnWidth(0,300);
    setItemDelegate(new QItemPropertyDelegate(this));
    setMinimumWidth(600);

    m_emptyItem = new QTreeWidgetItem(this);
    m_emptyItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);

    foreach(QAbstractSheetType * pro,m_sheetItem->getPropertys())
    {
        addProperty(pro);
    }

    connect(m_sheetItem,SIGNAL(propertyAdded(QAbstractSheetType*)),
            this,SLOT(addProperty(QAbstractSheetType*)));
    connect(m_sheetItem,SIGNAL(propertyDeled(QAbstractSheetType*)),
            this,SLOT(delProperty(QAbstractSheetType*)));
    connect(m_sheetItem,SIGNAL(propertyReplaced(QAbstractSheetType*,QAbstractSheetType*)),
            this,SLOT(propertyReplaced(QAbstractSheetType*,QAbstractSheetType*)));
}

QItemPropertyListView::~QItemPropertyListView()
{

}

void QItemPropertyListView::updateHeight()
{
    setFixedHeight(m_propertyToItem.keys().size()*24+24);
}

void QItemPropertyListView::addProperty(QAbstractSheetType *property)
{
    QTreeWidgetItem * item = new QTreeWidgetItem;
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    item->setText(0,property->getName());
    item->setToolTip(0,property->getName());
    item->setText(1,property->getValueText());
    item->setToolTip(1,property->getValueText());
    item->setIcon(1,property->getValueIcon());
    m_itemToProperty.insert(item,property);
    m_propertyToItem.insert(property,item);

    insertTopLevelItem(m_itemToProperty.keys().size()-1,item);

    emit needUpdateHeight();
}

void QItemPropertyListView::delProperty(QAbstractSheetType *property)
{
    QTreeWidgetItem * item = m_propertyToItem.value(property);

    if(item == NULL)
    {
        return;
    }
    m_propertyToItem.remove(property);
    m_itemToProperty.remove(item);

    delete item;
    emit needUpdateHeight();
}

void QItemPropertyListView::clickEditItem(QTreeWidgetItem *item, int index)
{
    editItem(item,index);
}

void QItemPropertyListView::propertyReplaced(QAbstractSheetType *oldPro, QAbstractSheetType *newPro)
{
    QTreeWidgetItem * item = m_propertyToItem.value(oldPro);
    item->setText(0,newPro->getName());
    item->setToolTip(0,newPro->getName());
    item->setText(1,newPro->getValueText());
    item->setToolTip(1,newPro->getValueText());
    item->setIcon(1,newPro->getValueIcon());
    m_itemToProperty.insert(item,newPro);
    m_propertyToItem.insert(newPro,item);
}
