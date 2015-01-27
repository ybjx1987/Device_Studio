#include "qpropertylistview.h"

QWidget * QPropertyListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget* wid = NULL;

    return wid;
}

void QPropertyListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect.adjusted(0,0,0,-1));
}

QPropertyListView::QPropertyListView()
{

}

QPropertyListView::~QPropertyListView()
{

}
