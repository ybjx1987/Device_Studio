#ifndef QITEMPROPERTYLISTVIEW_H
#define QITEMPROPERTYLISTVIEW_H

#include "../../../libs/platform/qbaselistview.h"

#include <QMap>

class QAbstractSheetType;

class QItemPropertyListView : public QBaseListView
{
    Q_OBJECT
public:
    QItemPropertyListView(QWidget * parent = NULL);
    ~QItemPropertyListView();

    void    addProperty(QAbstractSheetType * property);
    void    delProperty(QAbstractSheetType * property);

public:
    void    updateHeight();
protected:
    void clickEditItem(QTreeWidgetItem *item, int index);
protected:
    QMap<QAbstractSheetType*,QTreeWidgetItem*>  m_propertyToItem;
    QMap<QTreeWidgetItem*,QAbstractSheetType*>  m_itemToProperty;
    QTreeWidgetItem     *m_emptyItem;
};

#endif // QITEMPROPERTYLISTVIEW_H
