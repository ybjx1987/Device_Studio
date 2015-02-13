#include "qpagepane.h"

#include "../../../libs/kernel/host/qabstractwidgethost.h"

#include <QPainter>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>

QPagePane::QPagePane(QAbstractWidgetHost *host, QWidget *parent):
    QWidget(parent),
    m_host(host)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(10);
    effect->setColor(QColor(128,128,128));
    setGraphicsEffect(effect);
}

QPagePane::~QPagePane()
{

}

void QPagePane::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QWidget * wid = (QWidget*)m_host->getObject();
    QPixmap pixmap = wid->grab();

    p.drawPixmap(rect(),pixmap,pixmap.rect());

    QPen pen = p.pen();
    if(m_select)
    {
        pen.setColor(QColor(255,0,0));
        pen.setWidth(2);
    }
    else
    {
        pen.setColor(QColor(0,0,0));
        pen.setWidth(2);
    }
    p.setPen(pen);
    p.drawRect(rect().adjusted(1,1,-1,-1));
}

void QPagePane::mouseReleaseEvent(QMouseEvent *)
{
    emit select();
}

void QPagePane::mouseDoubleClickEvent(QMouseEvent *)
{
    emit doubleClick();
}

void QPagePane::setSelect(bool select)
{
    m_select = select;
    this->update();
}
