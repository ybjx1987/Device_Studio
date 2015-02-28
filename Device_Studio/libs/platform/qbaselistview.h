#ifndef QBASELISTVIEW_H
#define QBASELISTVIEW_H

#include "platformlibglobal.h"

#include <QTreeWidget>

class PLATFORM_EXPORT QBaseListView: public QTreeWidget
{
    Q_OBJECT
public:
    QBaseListView(QWidget* parent = NULL);
    QIcon   getExpandIcon();
protected:
    void mousePressEvent(QMouseEvent *event);
    void drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;
    virtual void clickEditItem(QTreeWidgetItem* item,int index);
protected:

    QIcon                                           m_expandIcon;
};

#endif // QBASELISTVIEW_H
