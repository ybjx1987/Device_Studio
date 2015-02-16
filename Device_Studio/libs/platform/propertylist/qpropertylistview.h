#ifndef QPROPERTYLISTVIEW_H
#define QPROPERTYLISTVIEW_H

#include "../qbaseitemdelegate.h"
#include "../qbaselistview.h"

#include <QUndoStack>

class QPropertyListView;
class QAbstractProperty;

class PLATFORM_EXPORT QPropertyListDelegate: public QBaseItemDelegate
{
    Q_OBJECT
public:
    QPropertyListDelegate(QPropertyListView* parent):m_listView(parent){}
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
protected:
    QPropertyListView   *m_listView;
};

class PLATFORM_EXPORT QPropertyListView : public QBaseListView
{
    Q_OBJECT
public:
    QPropertyListView(QWidget* parent = NULL);

    void    clear();

    void    setPropertys(const QList<QAbstractProperty*>    & propertys,
                         QUndoStack* undoStack = NULL);
protected slots:
    void    propertyValueChanged();
public slots:
    void    propertyValueEdit(QAbstractProperty* property,
                              const QVariant &value);
protected:
    void        updateView();
    void        insertItem(QAbstractProperty * property,
                           QAbstractProperty * parent = NULL);
    void        clickEditItem(QTreeWidgetItem *item, int index);

    friend class QPropertyListDelegate;
protected:
    QList<QAbstractProperty*>                       m_propertys;
    QMap<QString,QTreeWidgetItem*>                  m_groupToItem;
    QList<QTreeWidgetItem*>                         m_groups;
    QMap<QAbstractProperty*,QTreeWidgetItem*>       m_propertyToItem;
    QMap<QTreeWidgetItem*,QAbstractProperty*>       m_itemToProperty;
    QIcon                                           m_expandIcon;
    QUndoStack*                                     m_undoStack;
};

#endif // QPROPERTYLISTVIEW_H
