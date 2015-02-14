#include "qformpanel.h"

#include "formresizer.h"
#include "qdesignerdnditem.h"

#include "../../../../libs/kernel/host/qhostfactory.h"
#include "../../../../libs/kernel/host/qabstractwidgethost.h"
#include "../../../../libs/platform/undocommand/qaddhostundocommand.h"

#include <QVariant>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QDragEnterEvent>
#include <QUuid>

QFormPanel::QFormPanel(QAbstractWidgetHost *host, QWidget *parent):
    QScrollArea(parent),
    m_host(host),
    m_formResizer(new FormResizer(this)),
    m_undoStack(new QUndoStack)
{
    setWidget(m_formResizer);
    this->setFrameStyle(QFrame::NoFrame);
    ((QWidget*)m_host->getObject())->setAcceptDrops(true);
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
        else if(e->type() == QEvent::DragEnter)
        {
            return hostDragEnterEvent(host,(QDragEnterEvent*)e);
        }
        else if(e->type() == QEvent::Drop)
        {
            return hostDropEvent(host,(QDropEvent*)e);
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
    if(host->property("hostType") == "form")
    {
        QPainter p(wid);
        p.fillRect(wid->rect(),QColor(240,240,240));
        p.drawRect(wid->rect().adjusted(0,0,-1,-1));
//        int x_count = wid->width()/10;
//        int y_count = wid->height()/10;

//        for(int i=1; i<x_count;i++)
//        {
//            for(int j =1;j<y_count;j++)
//            {
//                p.drawPoint(10*i,10*j);
//            }
//        }

    }
    else
    {
        if(host->property("needFrame").toBool())
        {
            QPainter p(wid);
            QPen pen(Qt::DotLine);
            p.setPen(pen);
            p.drawRect(wid->rect().adjusted(0,0,-1,-1));
        }
        else if(host->property("acceptDrop").toBool())
        {
            QPainter p(wid);
            p.setBrush(Qt::transparent);
            p.fillRect(wid->rect(),QColor(128,128,128,80));
        }
    }

    return false;
}

void QFormPanel::paintEvent(QPaintEvent *)
{
    QPainter p(viewport());
    p.fillRect(this->rect(),QColor(255,255,255));
}

bool QFormPanel::hostDragEnterEvent(QAbstractWidgetHost *host, QDragEnterEvent *e)
{
    const QDesignerMimeData *mimeData=qobject_cast<const QDesignerMimeData*>(e->mimeData());
    if(mimeData!=NULL)
    {
        mimeData->acceptEvent(e);
    }

    if(host!=m_host)
    {
        m_host->setProperty("drag_enter",true);
        ((QWidget*)host->getObject())->update();
    }
    return false;
}

bool QFormPanel::hostDropEvent(QAbstractWidgetHost *host, QDropEvent *e)
{
    const QDesignerMimeData *mimeData=qobject_cast<const QDesignerMimeData*>(e->mimeData());
    if(mimeData==NULL)
    {
        return true;
    }

    mimeData->acceptEvent(e);

    QList<QDesignerDnDItemInterface*>   list=mimeData->items();

    QBaseUndoCommand *cmd = new QBaseUndoCommand;

    foreach(QDesignerDnDItemInterface *item,list)
    {
        if(item->type()==QDesignerDnDItemInterface::CopyDrop)
        {
            QAbstractHost *h=QHostFactory::createHost(item->name());
            if(h!=NULL)
            {
                h->setUuid(QUuid::createUuid().toString());
                QRect re=h->getPropertyValue("geometry").toRect();
                re.moveTo(e->pos()-item->hotSpot());
                h->setPropertyValue("geometry",re);

                QString name=h->getPropertyValue("objectName").toString();

                QStringList l;
                foreach(QAbstractHost* hh,host->getChildrenHost())
                {
                    l.append(hh->getPropertyValue("objectName").toString());
                }
                int count=1;
                QString t=name;
                while(1)
                {
                    if(l.contains(t))
                    {
                        t=name+"_"+QString::number(count);
                        count++;
                    }
                    else
                    {
                        break;
                    }
                }

                h->setPropertyValue("objectName",t);

                new QAddHostUndoCommand(host,h,host->getChildrenHost().size(),AHT_ADD,cmd);
            }
        }
        else
        {
        }
    }

    if(cmd->childCount()>0)
    {
        m_undoStack->push(cmd);
    }
    else
    {
        delete cmd;
    }

    if(host!=m_host)
    {
        host->setProperty("drag_enter",false);
        ((QWidget*)host->getObject())->update();
    }

    return true;
}

void QFormPanel::select(QAbstractWidgetHost *host)
{
    if(host == m_host || host == NULL)
    {
        m_formResizer->showHandle();
        emit hostSelected(m_host);
    }
    else
    {
        m_formResizer->hideHandle();
        emit hostSelected(host);
    }
}
