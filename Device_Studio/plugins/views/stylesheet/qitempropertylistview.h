#ifndef QITEMPROPERTYLISTVIEW_H
#define QITEMPROPERTYLISTVIEW_H

#include "../../../libs/platform/qbaselistview.h"

#include <QMap>

class QAbstractSheetProperty;

class QItemPropertyListView : public QBaseListView
{
    Q_OBJECT
public:
    QItemPropertyListView(QWidget * parent = NULL);
    ~QItemPropertyListView();

    void    addProperty(QAbstractSheetProperty * property);
    void    delProperty(QAbstractSheetProperty * property);

public:
    void    updateHeight();
protected:
    QMap<QAbstractSheetProperty*,QTreeWidgetItem*>  m_propertyToItem;
    QMap<QTreeWidgetItem*,QAbstractSheetProperty*>  m_itemToProperty;
};

#endif // QITEMPROPERTYLISTVIEW_H
