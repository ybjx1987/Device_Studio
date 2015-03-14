#include "qbaseitemdelegate.h"


#include <QApplication>
#include <QPainter>

void QBaseItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV3 opt=option;
    QColor c;

    if(!index.data(DarkRole).toBool())
    {
        c=QColor(BACKGROUND_COLOR);
        if(opt.features & QStyleOptionViewItemV2::Alternate)
        {
            c=c.lighter(112);
        }
    }
    else
    {
        c=option.palette.color(QPalette::Dark);
    }

    painter->fillRect(option.rect,c);
    opt.state &=~ QStyle::State_HasFocus;
    QItemDelegate::paint(painter,option,index);
    opt.palette.setCurrentColorGroup(QPalette::Active);
    QColor color=static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor,&opt));
    painter->setPen(color);

    if(!index.data(DarkRole).toBool())
    {
        int right=option.direction==Qt::LeftToRight?option.rect.right():option.rect.left();
        painter->drawLine(right,option.rect.y(),right,option.rect.bottom());
    }
}

QSize QBaseItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize sz=QItemDelegate::sizeHint(option,index);
    sz.setHeight(24);
    return sz;
}
