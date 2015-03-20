#ifndef QIMAGEVIEW_H
#define QIMAGEVIEW_H

#include <QGraphicsView>

#include <QGraphicsRectItem>
#include <QGraphicsItem>

class QImageView : public QGraphicsView
{
    Q_OBJECT
public:
    QImageView(QWidget * parent=NULL);
    ~QImageView();


    bool setImage(QByteArray array);

public slots:
    void resetToOriginalSize();
    void changedBackground();
    void changedOutline();
    void zoomIn();
    void zoomOut();
    void fitToScreen();

protected:
    void doScale(qreal factor);
    void wheelEvent(QWheelEvent *event);
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
protected:
    QGraphicsItem *     m_imageItem;
    QGraphicsRectItem * m_backgroundItem;
    QGraphicsRectItem * m_outlineItem;
};

#endif // QIMAGEVIEW_H
