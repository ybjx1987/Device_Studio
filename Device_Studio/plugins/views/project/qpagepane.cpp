#include "qpagepane.h"

#include "../../../libs/kernel/host/qabstractwidgethost.h"

#include <QPainter>
#include <QPixmap>

QPagePane::QPagePane(QAbstractWidgetHost *host, QWidget *parent):
    QWidget(parent),
    m_host(host)
{

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

    p.drawRect(rect().adjusted(0,0,-1,-1));
}
