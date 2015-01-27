#ifndef QBASELISTVIEW_H
#define QBASELISTVIEW_H

#include "platformlibglobal.h"

#include <QTreeWidget>

class QBaseListView: public QTreeWidget
{
    Q_OBJECT
protected:
    void drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;
};

#endif // QBASELISTVIEW_H
