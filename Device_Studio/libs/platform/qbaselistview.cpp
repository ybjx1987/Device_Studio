#include "qbaselistview.h"

#include "qbaseitemdelegate.h"
#include "stylehelper.h"

#include <QPainter>
#include <QHeaderView>
#include <QMouseEvent>
#include <QVariant>

QBaseListView::QBaseListView(QWidget *parent):
    QTreeWidget(parent)
{
    setFrameStyle(QFrame::NoFrame);
    setIconSize(QSize(18,18));
    setFocusPolicy(Qt::NoFocus);
    setItemDelegate(new QBaseItemDelegate);

    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::EditKeyPressed);
    setRootIsDecorated(false);

    QPalette p = this->palette();
    p.setColor(QPalette::Inactive,QPalette::Highlight,
               p.color(QPalette::Active,QPalette::Highlight));
    p.setColor(QPalette::Inactive,QPalette::HighlightedText,
               p.color(QPalette::Active,QPalette::HighlightedText));
    setPalette(p);

    m_expandIcon = StyleHelper::drawIndicatorIcon(this->palette(),this->style());
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

void QBaseListView::mousePressEvent(QMouseEvent *event)
{
    QTreeWidget::mousePressEvent(event);

    QTreeWidgetItem *item = itemAt(event->pos());
    if(item != NULL)
    {
        if(item->data(0,DarkRole).toBool())
        {
            if(event->pos().x()+header()->offset()<20)
            {
                item->setExpanded(!item->isExpanded());
            }
        }
        else
        {
            if(event->button() == Qt::LeftButton)
            {
                clickEditItem(item,header()->logicalIndexAt(event->pos()));
            }
        }
    }
}

void QBaseListView::clickEditItem(QTreeWidgetItem *item, int index)
{

}
