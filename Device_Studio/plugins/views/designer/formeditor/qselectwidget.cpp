#include "qselectwidget.h"

#include "../../../libs/kernel/host/qabstractwidgethost.h"
#include "../../../libs/platform/undocommand/qpropertyeditundocommand.h"
#include "../../../libs/kernel/property/qabstractproperty.h"

#include <QPainter>

#include <QMouseEvent>


WidgetHandle::WidgetHandle(QWidget *parent, Type t):
    QWidget(parent),
    m_type(t),
    m_host(NULL),
    m_current(false),
    m_undoStack(NULL)
{
    setAttribute(Qt::WA_NoChildEventsForParent);
    setMouseTracking(false);
    setAutoFillBackground(true);

    setBackgroundRole(QPalette::Text);
    setFixedSize(6, 6);

    updateCursor();
}

void WidgetHandle::updateCursor()
{
    switch (m_type)
    {
    case LeftTop:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case Top:
        setCursor(Qt::SizeVerCursor);
        break;
    case RightTop:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case Right:
        setCursor(Qt::SizeHorCursor);
        break;
    case RightBottom:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case Bottom:
        setCursor(Qt::SizeVerCursor);
        break;
    case LeftBottom:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case Left:
        setCursor(Qt::SizeHorCursor);
        break;
    default:
       setCursor(Qt::ArrowCursor);
       break;
    }
}

void WidgetHandle::setCurrent(bool b)
{
    m_current=b;
    this->update();
}

void WidgetHandle::setHost(QAbstractWidgetHost *host)
{
    m_host = host;
}

void WidgetHandle::setUndoStack(QUndoStack *undoStack)
{
    m_undoStack = undoStack;
}

void WidgetHandle::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(m_current? Qt::blue : Qt::black);
    p.setBrush(QBrush(QColor(m_current? Qt::darkBlue : Qt::black)));
    p.drawRect(0, 0, width() - 1, height() - 1);
}

void WidgetHandle::mousePressEvent(QMouseEvent *e)
{
    e->accept();

    if (!(m_host!=NULL && e->button() == Qt::LeftButton))
        return;

    QWidget *container = ((QWidget*)m_host->getObject())->parentWidget();

    m_origPressPos = container->mapFromGlobal(e->globalPos());
    m_geom = m_origGeom = m_host->getPropertyValue("geometry").toRect();
}


void WidgetHandle::mouseMoveEvent(QMouseEvent *e)
{
    if (!(m_host!=NULL && e->buttons() & Qt::LeftButton))
        return;

    e->accept();

    QWidget *container = ((QWidget*)m_host->getObject())->parentWidget();

    const QPoint rp = container->mapFromGlobal(e->globalPos());
    const QPoint d = rp - m_origPressPos;

    const QRect pr = container->rect();

    const QRect re= m_host->getPropertyValue("geometry").toRect();

    switch (m_type)
    {

    case LeftTop:
    {
        if (rp.x() > pr.width() - 2 * width() || rp.y() > pr.height() - 2 * height())
            return;

        int w = m_origGeom.width() - d.x();
        m_geom.setWidth(w);

        int h = m_origGeom.height() - d.y();
        m_geom.setHeight(h);

        const int dx = re.width() - w;
        const int dy = re.height() - h;
        trySetGeometry(re.x() + dx, re.y() + dy, w, h);
    }
    break;
    case Top:
    {
        if (rp.y() > pr.height() - 2 * height())
            return;

        int h = m_origGeom.height() - d.y();
        m_geom.setHeight(h);

        const int dy = re.height() - h;
        trySetGeometry(re.x(), re.y() + dy, re.width(), h);
    }
    break;
    case RightTop:
    {
        if (rp.x() < 2 * width() || rp.y() > pr.height() - 2 * height())
            return;

        int h = m_origGeom.height() - d.y();
        m_geom.setHeight(h);

        const int dy = re.height() - h;

        int w = m_origGeom.width() + d.x();
        m_geom.setWidth(w);

        trySetGeometry(re.x(), re.y() + dy, w, h);
    }
    break;
    case Right:
    {
        if (rp.x() < 2 * width())
            return;

        int w = m_origGeom.width() + d.x();
        m_geom.setWidth(w);

        tryResize(w, re.height());
    }
    break;
    case RightBottom:
    {
        if (rp.x() < 2 * width() || rp.y() < 2 * height())
            return;

        int w = m_origGeom.width() + d.x();
        m_geom.setWidth(w);

        int h = m_origGeom.height() + d.y();
        m_geom.setHeight(h);

        tryResize(w, h);
    }
    break;
    case Bottom:
    {
        if (rp.y() < 2 * height())
            return;

        int h = m_origGeom.height() + d.y();
        m_geom.setHeight(h);
        tryResize(re.width(), h);
    }
    break;
    case LeftBottom:
    {
        if (rp.x() > pr.width() - 2 * width() || rp.y() < 2 * height())
            return;

        int w = m_origGeom.width() - d.x();
        m_geom.setWidth(w);

        int h = m_origGeom.height() + d.y();
        m_geom.setHeight(h);

        int dx = re.width() - w;

        trySetGeometry(re.x() + dx, re.y(), w, h);
    }
    break;
    case Left:
    {
        if (rp.x() > pr.width() - 2 * width())
            return;

        int w = m_origGeom.width() - d.x();
        m_geom.setWidth(w);

        const int dx = re.width() - w;

        trySetGeometry(re.x() + dx, re.y(), w, re.height());
    }
    break;
    default: break;
    }
}

void WidgetHandle::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton)
        return;

    e->accept();
}

void WidgetHandle::trySetGeometry(int x, int y, int width, int height)
{
    QWidget * w = (QWidget*)m_host->getObject();
    int minw = w->minimumSize().width();
    minw = qMax(minw, 20);

    int minh = w->minimumSize().height();
    minh = qMax(minh, 20);

    if (qMax(minw, width) > w->maximumWidth() ||
         qMax(minh, height) > w->maximumHeight())
        return;

    if (width < minw && x != w->x())
        x -= minw - width;

    if (height < minh && y != w->y())
        y -= minh - height;

    QRect n = QRect(x,y,qMax(minw,width),qMax(minh,height));

    if(n != m_host->getPropertyValue("geometry").toRect()
            && m_undoStack != NULL)
    {
        QPropertyEditUndoCommand * cmd = new QPropertyEditUndoCommand(
                    m_host->getUuid(),"geometry",n,m_host->getPropertyValue("geometry"));

        m_undoStack->push(cmd);
    }
}

void WidgetHandle::tryResize(int width, int height)
{
    QWidget * w= (QWidget*)m_host->getObject();
    int minw = w->minimumSize().width();
    minw = qMax(minw, 16);

    int minh = w->minimumSize().height();
    minh = qMax(minh, 16);

    QRect n = QRect(w->x(),w->y(),qMax(minw,width),qMax(minh,height));

    if(n != m_host->getPropertyValue("geometry").toRect()
            && m_undoStack != NULL)
    {
        QPropertyEditUndoCommand * cmd = new QPropertyEditUndoCommand(
                    m_host->getUuid(),"geometry",n,m_host->getPropertyValue("geometry"));

        m_undoStack->push(cmd);
    }
}

WidgetSelection::WidgetSelection(QWidget *parent)   :
    m_host(0),
    m_formWindow(parent)
{
    for (int i = WidgetHandle::LeftTop; i < WidgetHandle::TypeCount; ++i)
    {
        m_handles[i] = new WidgetHandle(m_formWindow, static_cast<WidgetHandle::Type>(i));
    }
    hide();
}

void WidgetSelection::setCurrent(bool b)
{
    for (int i = WidgetHandle::LeftTop; i < WidgetHandle::TypeCount; ++i)
    {
        m_handles[i]->setCurrent(b);
    }
}

void WidgetSelection::setUndoStack(QUndoStack *undoStack)
{
    for (int i = WidgetHandle::LeftTop; i < WidgetHandle::TypeCount; ++i)
    {
        m_handles[i]->setUndoStack(undoStack);
    }
}

void WidgetSelection::setHost(QAbstractWidgetHost * host)
{
    m_host = host;
    for (int i = WidgetHandle::LeftTop; i < WidgetHandle::TypeCount; ++i)
    {
        m_handles[i]->setHost(m_host);
    }
    if(m_host == NULL)
    {
        this->hide();
        return;
    }
    updateGeometry();
    show();
}

bool WidgetSelection::isUsed() const
{
    return m_host != 0;
}

QAbstractWidgetHost *WidgetSelection::getHost()
{
    return m_host;
}

void WidgetSelection::updateGeometry()
{
    if (m_host == NULL)
        return;

    QWidget * wid = (QWidget*)m_host->getObject();

    QPoint p = wid->mapToGlobal(QPoint(0,0));
    p = m_formWindow->mapFromGlobal(p);
    const QRect r(p, wid->size());

    const int w = 6;
    const int h = 6;

    for (int i = WidgetHandle::LeftTop; i < WidgetHandle::TypeCount; ++i)
    {
        WidgetHandle *hndl = m_handles[ i ];
        if (!hndl)
            continue;
        switch (i)
        {
        case WidgetHandle::LeftTop:
            hndl->move(r.x() - w / 2, r.y() - h / 2);
            break;
        case WidgetHandle::Top:
            hndl->move(r.x() + r.width() / 2 - w / 2, r.y() - h / 2);
            break;
        case WidgetHandle::RightTop:
            hndl->move(r.x() + r.width() - w / 2, r.y() - h / 2);
            break;
        case WidgetHandle::Right:
            hndl->move(r.x() + r.width() - w / 2, r.y() + r.height() / 2 - h / 2);
            break;
        case WidgetHandle::RightBottom:
            hndl->move(r.x() + r.width() - w / 2, r.y() + r.height() - h / 2);
            break;
        case WidgetHandle::Bottom:
            hndl->move(r.x() + r.width() / 2 - w / 2, r.y() + r.height() - h / 2);
            break;
        case WidgetHandle::LeftBottom:
            hndl->move(r.x() - w / 2, r.y() + r.height() - h / 2);
            break;
        case WidgetHandle::Left:
            hndl->move(r.x() - w / 2, r.y() + r.height() / 2 - h / 2);
            break;
        default:
            break;
        }
    }
}

void WidgetSelection::hide()
{
    for (int i = WidgetHandle::LeftTop; i < WidgetHandle::TypeCount; ++i)
    {
        m_handles[i]->hide();
    }
}

void WidgetSelection::show()
{
    for (int i = WidgetHandle::LeftTop; i < WidgetHandle::TypeCount; ++i)
    {
        WidgetHandle *h = m_handles[ i ];
        h->show();
        h->raise();
    }
}

void WidgetSelection::update()
{
    for (int i = WidgetHandle::LeftTop; i < WidgetHandle::TypeCount; ++i)
    {
        m_handles[ i ]->update();
    }
}

Selection::Selection(QWidget *formwindow):
    m_current(NULL),
    m_formwindow(formwindow),
    m_undoStack(NULL)
{
}

Selection::~Selection()
{
    clearSelectionPool();
}

void Selection::clear()
{
    if (!m_usedSelections.empty())
    {
        const SelectionHash::iterator mend = m_usedSelections.end();
        for (SelectionHash::iterator it = m_usedSelections.begin(); it != mend; ++it)
        {
            it.value()->setHost(NULL);
        }
        m_usedSelections.clear();
    }
}

void  Selection::clearSelectionPool()
{
    clear();
    qDeleteAll(m_selectionPool);
    m_selectionPool.clear();
}

WidgetSelection *Selection::addHost(QAbstractWidgetHost *host)
{
    WidgetSelection *rc= m_usedSelections.value(host);
    if (rc != 0)
    {
        rc->show();
        return rc;
    }
    const SelectionPool::iterator pend = m_selectionPool.end();
    for (SelectionPool::iterator it = m_selectionPool.begin(); it != pend; ++it)
    {
        if (! (*it)->isUsed()) {
            rc = *it;
            break;
        }
    }

    if (rc == 0) {
        rc = new WidgetSelection(m_formwindow);
        rc->setUndoStack(m_undoStack);
        m_selectionPool.push_back(rc);

    }
    QAbstractProperty * pro = host->getProperty("geometry");
    connect(pro,SIGNAL(valueChanged(QVariant,QVariant)),
            this,SLOT(hostGeometryChanged()));
    m_usedSelections.insert(host, rc);
    rc->setHost(host);
    return rc;
}

void Selection::removeHost(QAbstractWidgetHost *host)
{
    WidgetSelection *s = m_usedSelections.value(host);
    if (s==NULL)
    {
        return;
    }
    QAbstractProperty * pro = host->getProperty("geometry");
    disconnect(pro,SIGNAL(valueChanged(QVariant,QVariant)),
            this,SLOT(hostGeometryChanged()));
    if(m_current==s)
    {
        m_current->setCurrent(false);
        m_current=NULL;
    }
    s->setHost(NULL);
    m_usedSelections.remove(host);
}

void Selection::repaintSelection(QAbstractWidgetHost * host)
{
    if (WidgetSelection *s = m_usedSelections.value(host))
    {
        s->update();
    }
}

void Selection::repaintSelection()
{
    const SelectionHash::iterator mend = m_usedSelections.end();
    for (SelectionHash::iterator it = m_usedSelections.begin(); it != mend; ++it)
    {
        it.value()->update();
    }
}

bool Selection::isHostSelected(QAbstractWidgetHost *host) const
{
    return  m_usedSelections.contains(host);
}

QList<QAbstractWidgetHost*> Selection::selectedHosts() const
{
    return m_usedSelections.keys();
}

void Selection::hide(QAbstractWidgetHost *host)
{
    if (WidgetSelection *s = m_usedSelections.value(host))
    {
        s->hide();
    }
}

void Selection::show(QAbstractWidgetHost *host)
{
    if (WidgetSelection *s = m_usedSelections.value(host))
    {
        s->show();
    }
}

void Selection::setCurrent(QAbstractWidgetHost *host)
{
    WidgetSelection *s = m_usedSelections.value(host);
    if(m_current==s)
    {
        return;
    }
    if(m_current!=NULL)
    {
        m_current->setCurrent(false);
    }
    m_current=s;
    if(m_current!=NULL)
    {
        m_current->setCurrent(true);
    }
}

void Selection::setUndoStack(QUndoStack *undoStack)
{
    m_undoStack = undoStack;

    const SelectionHash::iterator mend = m_usedSelections.end();
    for (SelectionHash::iterator it = m_usedSelections.begin(); it != mend; ++it)
    {
        it.value()->setUndoStack(undoStack);
    }
}

QAbstractWidgetHost* Selection::current()
{
    return m_current==NULL?NULL:m_current->getHost();
}

void Selection::hostGeometryChanged()
{
    QAbstractProperty * pro = (QAbstractProperty*)sender();

    const SelectionHash::iterator mend = m_usedSelections.end();
    for (SelectionHash::iterator it = m_usedSelections.begin(); it != mend; ++it)
    {
        if(it.key()->getUuid() == pro->getHostUuid())
        {
            it.value()->updateGeometry();
            return;
        }
    }
}
