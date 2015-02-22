#include "qformpanel.h"

#include "qdesignerdnditem.h"
#include "sizehandlerect.h"
#include "qselectwidget.h"

#include "../../../../libs/platform/undocommand/qpropertyeditundocommand.h"
#include "../../../../libs/kernel/host/qhostfactory.h"
#include "../../../../libs/kernel/host/qabstractwidgethost.h"
#include "../../../../libs/platform/undocommand/qaddhostundocommand.h"
#include "../../../../libs/kernel/property/qabstractproperty.h"
#include "../../../../libs/platform/qsoftactionmap.h"
#include "../../../../libs/platform/undocommand/qpropertyeditundocommandmore.h"

#include <QVariant>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QDragEnterEvent>
#include <QUuid>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>

QFormPanel::QFormPanel(QAbstractWidgetHost *host, QWidget *parent):
    QWidget(parent),
    m_host(host),
    m_undoStack(new QUndoStack),
    m_frame(new QFrame),
    m_selection(new Selection(m_frame))
{
    QWidget* wid = ((QWidget*)m_host->getObject());
    wid->setAcceptDrops(true);
    installHostEventFilter(m_host);

    QVBoxLayout *l = new QVBoxLayout;
    l->setMargin(0);
    l->setSpacing(0);
    l->addWidget(wid);
    m_frame->setLayout(l);
    m_frame->setAutoFillBackground(true);

    l = new QVBoxLayout;
    l->setMargin(FRAME_SIZE);
    l->setSpacing(0);
    l->addWidget(m_frame);
    setLayout(l);

    QList<QAbstractHost*>  list;
    list.append(m_host);

    while(list.size()>0)
    {
        QAbstractHost * h = list.takeFirst();
        m_objectToHost.insert(h->getObject(),(QAbstractWidgetHost*)h);
        list += h->getChildrenHost();
    }

    this->resize(wid->size()+QSize(2*FRAME_SIZE+1,2*FRAME_SIZE+1));

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setColor(QColor(192,192,192));
    effect->setBlurRadius(10);
    m_frame->setGraphicsEffect(effect);

    for(int i=SizeHandleRect::LeftTop;i<=SizeHandleRect::Left;i++)
    {
        m_handles[i]=new SizeHandleRect(this,(SizeHandleRect::Direction)i,m_frame);
        connect(m_handles[i],SIGNAL(sizeChanged(QSize)),
                this,SLOT(formResize(QSize)));
    }
    m_rubberBand = new QRubberBand(QRubberBand::Rectangle,wid);
    m_rubberBand->setVisible(false);

    connect(m_host,SIGNAL(hostAdded(QAbstractHost*,int)),
            this,SLOT(hostAdded(QAbstractHost*,int)));
    connect(m_host,SIGNAL(hostRemoved(QAbstractHost*)),
            this,SLOT(hostRemoved(QAbstractHost*)));

    setProperty("no-ManhattanStyle",true);
    m_frame->setObjectName("inner_frame_objectname");
    m_frame->setStyleSheet("#inner_frame_objectname{background-color:rgb(220,220,220);}");
}

QFormPanel::~QFormPanel()
{
    m_selection->clearSelectionPool();
    delete m_rubberBand;
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
        else if(e->type() == QEvent::Resize)
        {
            return hostResizeEvent(host,e);
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
    if(!m_clickPoint.isNull())
    {
        QRect re(QRect(m_clickPoint,e->pos()).normalized());
        m_rubberBand->setGeometry(re);
    }
    return true;
}

bool QFormPanel::hostDBMouseClick(QAbstractWidgetHost *host, QMouseEvent *e)
{
    return true;
}

bool QFormPanel::hostMousePress(QAbstractWidgetHost *host, QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
    {
        if(m_selection->selectedWidgets().contains((QWidget*)host->getObject()))
        {
            select(host);
            return true;
        }

    }
    else if(e->button() == Qt::LeftButton)
    {
        if(m_host==host)
        {
            m_clickPoint=e->pos();
            m_rubberBand->setGeometry(QRect(m_clickPoint,QSize()));
            m_rubberBand->show();
            m_selection->clear();
        }
        else
        {
            if(!(e->modifiers() && Qt::ControlModifier))
            {
                m_selection->clear();
            }
            select(host);
        }
    }
    return true;
}

bool QFormPanel::hostResizeEvent(QAbstractWidgetHost *host, QEvent *)
{
    QSize re=host->getPropertyValue("geometry").toRect().size();
    this->resize(re+QSize(FRAME_SIZE*2,FRAME_SIZE*2));
}

bool QFormPanel::hostMouseRelease(QAbstractWidgetHost *host, QMouseEvent *e)
{
    if(!m_clickPoint.isNull())
    {
        m_clickPoint=QPoint();
        QRect re=m_rubberBand->geometry();
        m_rubberBand->setGeometry(QRect(0,0,0,0));
        m_rubberBand->hide();

        m_selection->clear();

        foreach(QObject* obj,m_objectToHost.keys())
        {
            if(obj==m_host->getObject())
            {
                continue;
            }
            QAbstractWidgetHost *h=m_objectToHost.value(obj);
            if(h->getParent()!=m_host)
            {
                continue;
            }
            QWidget* wid=(QWidget*)obj;
            if(!(re & wid->geometry()).isNull())
            {
                m_selection->addWidget(wid);
            }
        }

        if(m_selection->selectedWidgets().size()>0)
        {
            select(m_objectToHost.value((QObject*)m_selection->selectedWidgets().first()));
        }
        else
        {
            select(m_host);
        }
        emit updateAction();
        this->update();

    }
    else
    {
        m_click=false;
    }
    return true;
}

bool QFormPanel::hostPaintEvent(QAbstractWidgetHost *host)
{
    QWidget* wid = (QWidget*)host->getObject();
    if(host->property("hostType") == "form")
    {
        QPainter p(wid);
        p.drawRect(wid->rect().adjusted(0,0,-1,-1));
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
    QPainter p(this);
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
                h->setPropertyValue("visible",true);
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
    QWidget * wid = (QWidget *)host->getObject();
    if(host == m_host || host == NULL)
    {
        m_selection->clear();
        setHandelVisible(true);
        emit hostSelected(m_host);
    }
    else
    {
        setHandelVisible(false);
        if(m_selection->selectedWidgets().contains(wid))
        {
            m_selection->setCurrent(wid);
        }
        else
        {
            m_selection->addWidget(wid);
        }
        if(m_selection->selectedWidgets().size() == 1)
        {
            m_selection->setCurrent(wid);
        }
        emit hostSelected(host);
    }

    updateAction();
}

QUndoStack * QFormPanel::getUndoStack()
{
    return m_undoStack;
}

void QFormPanel::formResize(const QSize &size)
{
    QRect rect = m_host->getPropertyValue("geometry").toRect();
    rect.setWidth(size.width());
    rect.setHeight(size.height());
    QPropertyEditUndoCommand *cmd = new QPropertyEditUndoCommand(
                m_host->getUuid(),"geometry",
                rect,m_host->getPropertyValue("geometry"));
    m_undoStack->push(cmd);
    this->resize(size+QSize(2*FRAME_SIZE,2*FRAME_SIZE));
}

void QFormPanel::setOwner(QWidget *owner)
{
    m_owner = owner;
}

QWidget* QFormPanel::getOwner()
{
    return m_owner;
}

void QFormPanel::updateGeometry()
{
    const QRect &geom=m_frame->geometry();

    const int w=6;
    const int h=6;

    for(int i=0;i<8;i++)
    {
        switch(m_handles[i]->dir())
        {
        case SizeHandleRect::LeftTop:
            m_handles[i]->move(geom.x()-w/2,geom.y()-h/2);
            break;
        case SizeHandleRect::Top:
            m_handles[i]->move(geom.x()+geom.width()/2-w/2,geom.y()-h/2);
            break;
        case SizeHandleRect::RightTop:
            m_handles[i]->move(geom.x()+geom.width()-w/2,geom.y()-h/2);
            break;
        case SizeHandleRect::Right:
            m_handles[i]->move(geom.x()+geom.width()-w/2,geom.y()+geom.height()/2-h/2);
            break;
        case SizeHandleRect::RightBottom:
            m_handles[i]->move(geom.x()+geom.width()-w/2,geom.y()+geom.height()-h/2);
            break;
        case SizeHandleRect::Bottom:
            m_handles[i]->move(geom.x()+geom.width()/2-w/2,geom.y()+geom.height()-h/2);
            break;
        case SizeHandleRect::LeftBottom:
            m_handles[i]->move(geom.x()-w/2,geom.y()+geom.height()-h/2);
            break;
        case SizeHandleRect::Left:
            m_handles[i]->move(geom.x()-w/2,geom.y()+geom.height()/2-h/2);
            break;
        }
    }
}

void QFormPanel::resizeEvent(QResizeEvent *)
{
    updateGeometry();
}

void QFormPanel::setHandelVisible(bool visible)
{
    for(int i=0;i<8;i++)
    {
        m_handles[i]->setVisible(visible);
    }
}

void QFormPanel::hostAdded(QAbstractHost *host, int)
{
    QList<QAbstractHost*>  list;
    list.append(host);

    while(list.size()>0)
    {
        QAbstractHost * h = list.takeFirst();
        m_objectToHost.insert(h->getObject(),(QAbstractWidgetHost*)h);
        list += h->getChildrenHost();
    }
    installHostEventFilter((QAbstractWidgetHost*)host);

    m_selection->clear();
    select((QAbstractWidgetHost*)host);
}

void QFormPanel::hostRemoved(QAbstractHost *host)
{
    removeHostEventFilter((QAbstractWidgetHost*)host);
    if(m_selection->selectedWidgets().contains((QWidget*)host->getObject()))
    {
        m_selection->removeWidget((QWidget*)host->getObject());
        if(m_selection->selectedWidgets().size()>0)
        {
            if(m_selection->current() == NULL)
            {
                select(m_objectToHost.value(m_selection->selectedWidgets().first()));
            }
        }
        else
        {
            select(m_host);
        }
    }
    QList<QAbstractHost*>  list;
    list.append(host);
    while(list.size()>0)
    {
        QAbstractHost * h = list.takeFirst();
        m_objectToHost.remove(h->getObject());
        list += h->getChildrenHost();
    }
}

void QFormPanel::sameLeft()
{
    if(m_undoStack == NULL)
    {
        return;
    }
    QWidgetList list = m_selection->selectedWidgets();

    QList<QAbstractHost*> hosts;
    foreach(QWidget* wid,list)
    {
        hosts.append(m_objectToHost.value(wid));
    }

    QPropertyEditUndoCommandMore *cmd =
            new QPropertyEditUndoCommandMore("geometry");

    QRect re = m_selection->current()->geometry();

    foreach(QAbstractHost * host,hosts)
    {
        QRect r = host->getPropertyValue("geometry").toRect();
        r.setRect(re.left(),r.top(),r.width(),r.height());
        cmd->add(host->getUuid(),host->getPropertyValue("geometry"),
                 r);
    }
    m_undoStack->push(cmd);
}

void QFormPanel::sameTop()
{
    if(m_undoStack == NULL)
    {
        return;
    }
    QWidgetList list = m_selection->selectedWidgets();

    QList<QAbstractHost*> hosts;
    foreach(QWidget* wid,list)
    {
        hosts.append(m_objectToHost.value(wid));
    }

    QPropertyEditUndoCommandMore *cmd =
            new QPropertyEditUndoCommandMore("geometry");

    QRect re = m_selection->current()->geometry();

    foreach(QAbstractHost * host,hosts)
    {
        QRect r = host->getPropertyValue("geometry").toRect();
        r.setRect(r.left(),re.top(),r.width(),r.height());
        cmd->add(host->getUuid(),host->getPropertyValue("geometry"),
                 r);
    }
    m_undoStack->push(cmd);
}

void QFormPanel::sameRight()
{
    if(m_undoStack == NULL)
    {
        return;
    }
    QWidgetList list = m_selection->selectedWidgets();

    QList<QAbstractHost*> hosts;
    foreach(QWidget* wid,list)
    {
        hosts.append(m_objectToHost.value(wid));
    }

    QPropertyEditUndoCommandMore *cmd =
            new QPropertyEditUndoCommandMore("geometry");

    QRect re = m_selection->current()->geometry();

    foreach(QAbstractHost * host,hosts)
    {
        QRect r = host->getPropertyValue("geometry").toRect();
        r.setRect(re.left()+re.width()-r.width(),r.top(),r.width(),r.height());
        cmd->add(host->getUuid(),host->getPropertyValue("geometry"),
                 r);
    }
    m_undoStack->push(cmd);
}

void QFormPanel::sameBottom()
{
    if(m_undoStack == NULL)
    {
        return;
    }
    QWidgetList list = m_selection->selectedWidgets();

    QList<QAbstractHost*> hosts;
    foreach(QWidget* wid,list)
    {
        hosts.append(m_objectToHost.value(wid));
    }

    QPropertyEditUndoCommandMore *cmd =
            new QPropertyEditUndoCommandMore("geometry");

    QRect re = m_selection->current()->geometry();

    foreach(QAbstractHost * host,hosts)
    {
        QRect r = host->getPropertyValue("geometry").toRect();
        r.setRect(r.left(),re.top()+re.height()-r.height(),r.width(),r.height());
        cmd->add(host->getUuid(),host->getPropertyValue("geometry"),
                 r);
    }
    m_undoStack->push(cmd);
}

void QFormPanel::sameVCenter()
{
    if(m_undoStack == NULL)
    {
        return;
    }
    QWidgetList list = m_selection->selectedWidgets();

    QList<QAbstractHost*> hosts;
    foreach(QWidget* wid,list)
    {
        hosts.append(m_objectToHost.value(wid));
    }

    QPropertyEditUndoCommandMore *cmd =
            new QPropertyEditUndoCommandMore("geometry");

    QRect re = m_selection->current()->geometry();

    foreach(QAbstractHost * host,hosts)
    {
        QRect r = host->getPropertyValue("geometry").toRect();
        r.setRect(re.left()+(re.width()-r.width())/2,r.top(),r.width(),r.height());
        cmd->add(host->getUuid(),host->getPropertyValue("geometry"),
                 r);
    }
    m_undoStack->push(cmd);
}

void QFormPanel::sameHCenter()
{
    if(m_undoStack == NULL)
    {
        return;
    }
    QWidgetList list = m_selection->selectedWidgets();

    QList<QAbstractHost*> hosts;
    foreach(QWidget* wid,list)
    {
        hosts.append(m_objectToHost.value(wid));
    }

    QPropertyEditUndoCommandMore *cmd =
            new QPropertyEditUndoCommandMore("geometry");

    QRect re = m_selection->current()->geometry();

    foreach(QAbstractHost * host,hosts)
    {
        QRect r = host->getPropertyValue("geometry").toRect();
        r.setRect(r.left(),re.top()+(re.height()-r.height())/2,r.width(),r.height());
        cmd->add(host->getUuid(),host->getPropertyValue("geometry"),
                 r);
    }
    m_undoStack->push(cmd);
}

void QFormPanel::sameWidth()
{
    if(m_undoStack == NULL)
    {
        return;
    }
    QWidgetList list = m_selection->selectedWidgets();

    QList<QAbstractHost*> hosts;
    foreach(QWidget* wid,list)
    {
        hosts.append(m_objectToHost.value(wid));
    }

    QPropertyEditUndoCommandMore *cmd =
            new QPropertyEditUndoCommandMore("geometry");

    QRect re = m_selection->current()->geometry();

    foreach(QAbstractHost * host,hosts)
    {
        QRect r = host->getPropertyValue("geometry").toRect();
        r.setRect(r.left(),r.top(),re.width(),r.height());
        cmd->add(host->getUuid(),host->getPropertyValue("geometry"),
                 r);
    }
    m_undoStack->push(cmd);
}

void QFormPanel::sameHeight()
{
    if(m_undoStack == NULL)
    {
        return;
    }
    QWidgetList list = m_selection->selectedWidgets();

    QList<QAbstractHost*> hosts;
    foreach(QWidget* wid,list)
    {
        hosts.append(m_objectToHost.value(wid));
    }

    QPropertyEditUndoCommandMore *cmd =
            new QPropertyEditUndoCommandMore("geometry");

    QRect re = m_selection->current()->geometry();

    foreach(QAbstractHost * host,hosts)
    {
        QRect r = host->getPropertyValue("geometry").toRect();
        r.setRect(r.left(),r.top(),r.width(),re.height());
        cmd->add(host->getUuid(),host->getPropertyValue("geometry"),
                 r);
    }
    m_undoStack->push(cmd);
}

void QFormPanel::sameGeometry()
{
    if(m_undoStack == NULL)
    {
        return;
    }
    QWidgetList list = m_selection->selectedWidgets();

    QList<QAbstractHost*> hosts;
    foreach(QWidget* wid,list)
    {
        hosts.append(m_objectToHost.value(wid));
    }

    QPropertyEditUndoCommandMore *cmd =
            new QPropertyEditUndoCommandMore("geometry");

    QRect re = m_selection->current()->geometry();

    foreach(QAbstractHost * host,hosts)
    {
        QRect r = host->getPropertyValue("geometry").toRect();
        r.setRect(r.left(),r.top(),re.width(),re.height());
        cmd->add(host->getUuid(),host->getPropertyValue("geometry"),
                 r);
    }
    m_undoStack->push(cmd);
}

bool QFormPanel::enableAction()
{
    return m_selection->selectedWidgets().size()>1;
}
