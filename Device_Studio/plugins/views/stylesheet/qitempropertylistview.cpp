#include "qitempropertylistview.h"

#include "../../../libs/platform/qbaseitemdelegate.h"
#include "../../../libs/kernel/stylesheet/qsheetpropertyfactory.h"
#include "../../../libs/kernel/stylesheet/type/qabstractsheettype.h"

#include <QHeaderView>
#include <QComboBox>

class QItemPropertyDelegate: public QBaseItemDelegate
{
public:
    QItemPropertyDelegate(QItemPropertyListView* view):m_listView(view){}
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void    drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
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
        comboBox->addItems(list);
        wid = comboBox;
    }

    if(wid != NULL)
    {
        wid->setProperty("no-ManhattanStyle",true);
    }
    return wid;
}

void QItemPropertyDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    QStyleOptionViewItem opt = option;
    opt.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;
    QBaseItemDelegate::drawDisplay(painter,opt,rect.adjusted(0,0,-10,0),text);
}

QItemPropertyListView::QItemPropertyListView(QWidget * parent ):
    QBaseListView(parent)
{
    header()->hide();
    setColumnCount(2);
    setColumnWidth(0,300);
    setItemDelegate(new QItemPropertyDelegate(this));
    setMinimumWidth(600);

    m_emptyItem = new QTreeWidgetItem(this);
    m_emptyItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
}

QItemPropertyListView::~QItemPropertyListView()
{

}

void QItemPropertyListView::updateHeight()
{
    setFixedHeight(m_propertyToItem.keys().size()*22+22);
}

void QItemPropertyListView::addProperty(QAbstractSheetType *property)
{

}

void QItemPropertyListView::delProperty(QAbstractSheetType *property)
{

}

void QItemPropertyListView::clickEditItem(QTreeWidgetItem *item, int index)
{
    editItem(item,index);
}
