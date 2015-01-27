#ifndef QPROPERTYLISTVIEW_H
#define QPROPERTYLISTVIEW_H

#include "../qbaseitemdelegate.h"
#include "../qbaselistview.h"

class QPropertyListView;

class PLATFORM_EXPORT QPropertyListDelegate: public QBaseItemDelegate
{
    Q_OBJECT
public:
    QPropertyListDelegate(QPropertyListView* parent):m_listView(parent){}
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
protected:
    QPropertyListView   *m_listView;
};

class PLATFORM_EXPORT QPropertyListView : public QBaseListView
{
    Q_OBJECT
public:
    QPropertyListView();
    ~QPropertyListView();
};

#endif // QPROPERTYLISTVIEW_H
