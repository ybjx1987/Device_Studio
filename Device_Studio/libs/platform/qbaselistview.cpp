#include "qbaselistview.h"

#include "qbaseitemdelegate.h"

#include <QPainter>

QBaseListView::QBaseListView(QWidget *parent):
    QTreeWidget(parent)
{

}

void QBaseListView::drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const
{
    QColor c;

    QStyleOptionViewItem opt = options;
    if(index.data(DarkRole).toBool())
    {
        c = opt.palette.color(QPalette::Dark);
    }
    else
    {
        c=QColor(BACKGROUND_COLOR);
    }
    painter->fillRect(options.rect,c);
    opt.palette.setColor(QPalette::AlternateBase,c.lighter(112));
    QTreeWidget::drawRow(painter,opt,index);
}
