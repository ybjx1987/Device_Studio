#ifndef QBASEITEMDELEGATE_H
#define QBASEITEMDELEGATE_H

#include "platformlibglobal.h"

#include <QItemDelegate>

#define DarkRole   Qt::UserRole+100
#define BACKGROUND_COLOR    255,230,191

class PLATFORM_EXPORT QBaseItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // QBASEITEMDELEGATE_H
