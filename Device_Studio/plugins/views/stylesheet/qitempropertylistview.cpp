#include "qitempropertylistview.h"

#include <QHeaderView>

QItemPropertyListView::QItemPropertyListView(QWidget * parent ):
    QBaseListView(parent)
{
    header()->hide();
    setColumnCount(2);
    setColumnWidth(0,300);

    setMinimumWidth(600);
}

QItemPropertyListView::~QItemPropertyListView()
{

}

void QItemPropertyListView::updateHeight()
{
    setFixedHeight(m_propertyToItem.keys().size()*22);
}

void QItemPropertyListView::addProperty(QAbstractSheetProperty *property)
{

}

void QItemPropertyListView::delProperty(QAbstractSheetProperty *property)
{

}
