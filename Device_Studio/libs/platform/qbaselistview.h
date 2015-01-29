#ifndef QBASELISTVIEW_H
#define QBASELISTVIEW_H

#include "platformlibglobal.h"

#include <QTreeWidget>

class PLATFORM_EXPORT QBaseListView: public QTreeWidget
{
    Q_OBJECT
public:
    QBaseListView(QWidget* parent = NULL);
protected:
    void drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;
};

#endif // QBASELISTVIEW_H
