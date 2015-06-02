#include "qimageview.h"

#include <QPainter>
#include <QImageReader>
#include <QBuffer>
#include <QWheelEvent>
#include <qmath.h>

QImageView::QImageView(QWidget * parent):
    QGraphicsView(parent),
    m_imageItem(NULL),
    m_backgroundItem(NULL),
    m_outlineItem(NULL)
{
    setScene(new QGraphicsScene(this));
    setTransformationAnchor(AnchorViewCenter);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);
    setFrameShape(QFrame::NoFrame);
    setRenderHint(QPainter::SmoothPixmapTransform);



    QPixmap tilePixmap(64,64);

    tilePixmap.fill(Qt::white);

    QPainter tilePainter(&tilePixmap);

    QColor color(220,220,220);
    tilePainter.fillRect(0,0,0x20,0x20,color);
    tilePainter.fillRect(0x20,0x20,0x20,0x20,color);
    tilePainter.end();

    setBackgroundBrush(tilePixmap);
}

QImageView::~QImageView()
{

}

void QImageView::drawBackground(QPainter *painter, const QRectF &)
{
    painter->save();
    painter->resetTransform();
    painter->drawTiledPixmap(viewport()->rect(),backgroundBrush().texture());
    painter->restore();
}

void QImageView::resetToOriginalSize()
{
    resetTransform();
}

void QImageView::changedBackground()
{
    if(m_backgroundItem == NULL)
    {
        return;
    }
    if(m_backgroundItem->isVisible())
    {
        m_backgroundItem->setVisible(false);
    }
    else
    {
        m_backgroundItem->setVisible(true);
    }
}

void QImageView::changedOutline()
{
    if(m_outlineItem == NULL)
    {
        return;
    }
    if(m_outlineItem->isVisible())
    {
        m_outlineItem->setVisible(false);
    }
    else
    {
        m_outlineItem->setVisible(true);
    }
}

void QImageView::doScale(qreal factor)
{
    qreal currentScale=transform().m11();
    qreal newScale=currentScale*factor;
    qreal actualFactor=factor;
    if(newScale>1000)
    {
        actualFactor=1000./currentScale;
    }
    else if(newScale<0.001)
    {
        actualFactor=0.001/currentScale;
    }
    scale(actualFactor,actualFactor);
}

void QImageView::zoomIn()
{
    doScale(1.2);
}

void QImageView::zoomOut()
{
    doScale(1/1.2);
}

bool QImageView::setImage(QByteArray array)
{
    QBuffer b(&array);
    b.open(QIODevice::ReadOnly);
    QByteArray format=QImageReader::imageFormat(&b);

    resetToOriginalSize();

    QGraphicsScene *s=scene();
    s->clear();

    if(format.isEmpty())
    {
        b.close();
        m_backgroundItem=NULL;
        m_outlineItem=NULL;
        return false;
    }

    bool drawBackground=(m_backgroundItem?m_backgroundItem->isVisible():false);
    bool drawOutline=(m_outlineItem?m_outlineItem->isVisible():true);

    QPixmap pixmap;
    pixmap=QPixmap::fromImage(QImage::fromData(array));
    QGraphicsPixmapItem *pixmapItem=new QGraphicsPixmapItem(pixmap);
    pixmapItem->setTransformationMode(Qt::SmoothTransformation);
    m_imageItem=pixmapItem;
    //emit imageSizeChanged(pixmap.size());

    m_imageItem->setCacheMode(QGraphicsItem::NoCache);
    m_imageItem->setZValue(0);

    m_backgroundItem=new QGraphicsRectItem(m_imageItem->boundingRect());
    m_backgroundItem->setBrush(Qt::white);
    m_backgroundItem->setPen(Qt::NoPen);
    m_backgroundItem->setVisible(drawBackground);
    m_backgroundItem->setZValue(-1);

    m_outlineItem=new QGraphicsRectItem(m_imageItem->boundingRect());
    QPen outline(Qt::black,1,Qt::DashLine);
    outline.setCosmetic(true);
    m_outlineItem->setPen(outline);
    m_outlineItem->setBrush(Qt::NoBrush);
    m_outlineItem->setVisible(drawOutline);
    m_outlineItem->setZValue(1);

    s->addItem(m_backgroundItem);
    s->addItem(m_imageItem);
    s->addItem(m_outlineItem);

    if(m_imageItem->boundingRect().height()==0 && m_imageItem->boundingRect().width()==0)
    {
        return false;
    }
    //emitScaleFactor();
    return true;
}

void QImageView::fitToScreen()
{
    if(m_imageItem == NULL)
    {
        return;
    }
    fitInView(m_imageItem,Qt::KeepAspectRatio);
}

void QImageView::wheelEvent(QWheelEvent *event)
{
    qreal factor=qPow(1.2,event->delta()/240.0);
    doScale(factor);
    event->accept();
}
