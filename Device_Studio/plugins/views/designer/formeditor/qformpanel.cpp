#include "qformpanel.h"

#include "formresizer.h"

#include "../../../../libs/kernel/host/qabstractwidgethost.h"

#include <QVariant>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

QFormPanel::QFormPanel(QAbstractWidgetHost *host, QWidget *parent):
    QScrollArea(parent),
    m_host(host),
    m_formResizer(new FormResizer(this))
{
    setWidget(m_formResizer);
    this->setFrameStyle(QFrame::NoFrame);

    m_formResizer->setWidget((QWidget*)m_host->getObject());

    installHostEventFilter(m_host);

    QList<QAbstractHost*>  list;
    list.append(m_host);

    while(list.size()>0)
    {
        QAbstractHost * h = list.takeFirst();
        m_objectToHost.insert(h->getObject(),(QAbstractWidgetHost*)h);
        list += h->getChildrenHost();
    }

    m_formResizer->hideHandle();
}

QFormPanel::~QFormPanel()
{
    removeHostEventFilter(m_host);
}

void QFormPanel::installHostEventFilter(QAbstractWidgetHost *host)
{
    if(host == NULL)
    {
        return;
    }

    host->getObject()->installEventFilter(this);

    foreach(QAbstractHost * h,host->getChildrenHost())
    {
        installHostEventFilter((QAbstractWidgetHost*)h);
    }
}

void QFormPanel::removeHostEventFilter(QAbstractWidgetHost *host)
{
    if(host == NULL)
    {
        return;
    }

    host->getObject()->removeEventFilter(this);

    foreach(QAbstractHost * h,host->getChildrenHost())
    {
        removeHostEventFilter((QAbstractWidgetHost*)h);
    }
}

bool QFormPanel::eventFilter(QObject *o, QEvent *e)
{
    QAbstractWidgetHost *host = getHost(o);

    if(host != NULL)
    {
        if(e->type() == QEvent::MouseButtonRelease)
        {
            return hostMouseRelease(host,(QMouseEvent*)e);
        }
        else if(e->type() == QEvent::MouseButtonPress)
        {
            return hostMousePress(host,(QMouseEvent*)e);
        }
        else if(e->type() == QEvent::MouseMove)
        {
            return hostMouseMove(host,(QMouseEvent*)e);
        }
        else if(e->type() == QEvent::MouseButtonDblClick)
        {
            return hostDBMouseClick(host,(QMouseEvent*)e);
        }
        else if(e->type() == QEvent::Paint)
        {
            return hostPaintEvent(host);
        }
    }

    return false;
}

QAbstractWidgetHost *QFormPanel::getHost(QObject *obj)
{
    QAbstractWidgetHost *host = NULL;
    while(obj != NULL)
    {
        host = m_objectToHost.value(obj);
        if(host != NULL)
        {
            return host;
        }
        else
        {
            obj = obj->parent();
        }
    }
    return host;
}

bool QFormPanel::hostMouseMove(QAbstractWidgetHost *host, QMouseEvent *e)
{
    return false;
}

bool QFormPanel::hostDBMouseClick(QAbstractWidgetHost *host, QMouseEvent *e)
{
    return false;
}

bool QFormPanel::hostMousePress(QAbstractWidgetHost *host, QMouseEvent *e)
{
    return false;
}

bool QFormPanel::hostMouseRelease(QAbstractWidgetHost *host, QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_formResizer->showHandle();
    }
    else
    {
        m_formResizer->hideHandle();
    }
    return false;
}

bool QFormPanel::hostPaintEvent(QAbstractWidgetHost *host)
{
    QWidget* wid = (QWidget*)host->getObject();
    QPainter p(wid);
    if(host->property("hostType") == "form")
    {
        p.fillRect(wid->rect(),QColor(240,240,240));
        p.drawRect(wid->rect().adjusted(0,0,-1,-1));
        int x_count = wid->width()/10;
        int y_count = wid->height()/10;

        for(int i=1; i<x_count;i++)
        {
            for(int j =1;j<y_count;j++)
            {
                p.drawPoint(10*i,10*j);
            }
        }

    }
    else
    {
        if(host->property("needFrame").toBool())
        {
            QPen pen(Qt::DotLine);
            p.setPen(pen);
            p.drawRect(wid->rect().adjusted(0,0,-1,-1));
        }
    }
    return false;
}

void QFormPanel::paintEvent(QPaintEvent *)
{
    QPainter p(viewport());
    p.fillRect(this->rect(),QColor(255,255,255));
}
