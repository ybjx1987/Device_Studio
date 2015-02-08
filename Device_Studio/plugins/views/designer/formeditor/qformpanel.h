#ifndef QFORMPANEL_H
#define QFORMPANEL_H

#include <QScrollArea>
#include <QMap>
#include <QUndoStack>

class QAbstractWidgetHost;
class QFormContainer;
class FormResizer;

class QFormPanel : public QScrollArea
{
    Q_OBJECT
public:
    explicit QFormPanel(QAbstractWidgetHost * host,QWidget *parent = 0);
    ~QFormPanel();
protected:
    void    installHostEventFilter(QAbstractWidgetHost * host);
    void    removeHostEventFilter(QAbstractWidgetHost * host);

    bool    hostMousePress(QAbstractWidgetHost *host,QMouseEvent *e);
    bool    hostMouseRelease(QAbstractWidgetHost *host,QMouseEvent *e);
    bool    hostMouseMove(QAbstractWidgetHost *host,QMouseEvent *e);
    bool    hostDBMouseClick(QAbstractWidgetHost * host,QMouseEvent *e);

    bool    hostPaintEvent(QAbstractWidgetHost * host);

    bool    hostDragEnterEvent(QAbstractWidgetHost* host,QDragEnterEvent *e);
    bool    hostDropEvent(QAbstractWidgetHost* host,QDropEvent * e);
protected:
    void    paintEvent(QPaintEvent *);
protected:
    bool    eventFilter(QObject *, QEvent *);

    QAbstractWidgetHost * getHost(QObject * obj);
protected:
    QAbstractWidgetHost * m_host;
    FormResizer         * m_formResizer;
    QMap<QObject*,QAbstractWidgetHost*>     m_objectToHost;
    QUndoStack          * m_undoStack;
};

#endif // QFORMPANEL_H
