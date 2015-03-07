#ifndef QITEMPROPERTYLISTVIEW_H
#define QITEMPROPERTYLISTVIEW_H

#include "../../../libs/platform/qbaselistview.h"

#include <QMap>

class QAbstractSheetType;
class QStyleSheetItem;
class QItemPropertyDelegate;

class QItemPropertyListView : public QBaseListView
{
    Q_OBJECT
public:
    QItemPropertyListView(QStyleSheetItem * item,QWidget * parent = NULL);
    ~QItemPropertyListView();

protected slots:
    void    addProperty(QAbstractSheetType * property);
    void    delProperty(QAbstractSheetType * property);
    void    propertyReplaced(QAbstractSheetType * oldPro,
                             QAbstractSheetType * newPro);
    void    needUpdate();
signals:
    void    needUpdateHeight();
public:
    void    updateHeight();
protected:
    friend class QItemPropertyDelegate;
protected:
    void clickEditItem(QTreeWidgetItem *item, int index);
protected:
    QMap<QAbstractSheetType*,QTreeWidgetItem*>  m_propertyToItem;
    QMap<QTreeWidgetItem*,QAbstractSheetType*>  m_itemToProperty;
    QTreeWidgetItem     *m_emptyItem;
    QStyleSheetItem     *m_sheetItem;
};

#endif // QITEMPROPERTYLISTVIEW_H
