#ifndef QSELECTWIDGET_H
#define QSELECTWIDGET_H

#include <QWidget>
#include <QHash>
#include <QUndoStack>

class QAbstractWidgetHost;

class WidgetHandle: public QWidget
{
    Q_OBJECT
public:
    enum Type
    {
        LeftTop,
        Top,
        RightTop,
        Right,
        RightBottom,
        Bottom,
        LeftBottom,
        Left,

        TypeCount
    };
    WidgetHandle(QWidget* parent,Type t);

    void    setHost(QAbstractWidgetHost *host);
    void    setCurrent(bool b);
    void    setUndoStack(QUndoStack * undoStack);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
protected:
    void    updateCursor();
    void    trySetGeometry(int x, int y, int width, int height);
    void    tryResize(int width, int height);
protected:
    Type        m_type;
    QAbstractWidgetHost *   m_host;
    bool        m_current;
    QPoint      m_origPressPos;
    QRect       m_geom, m_origGeom;
    QUndoStack  *m_undoStack;
};

class WidgetSelection: public QObject
{
    Q_OBJECT
public:
    WidgetSelection(QWidget *parent);

    void setHost(QAbstractWidgetHost *host);
    QAbstractWidgetHost *getHost();
    bool isUsed() const;

    void hide();
    void show();
    void update();
    void updateGeometry();

    void setCurrent(bool b);
    void setUndoStack(QUndoStack * undoStack);
protected:
    WidgetHandle *m_handles[WidgetHandle::TypeCount];
    QAbstractWidgetHost     *m_host;
    QWidget     *m_formWindow;
};

class Selection :   public QObject
{
    Q_OBJECT
public:
    Selection(QWidget *formwindow);
    ~Selection();

    void clear();

    void  clearSelectionPool();

    void repaintSelection(QAbstractWidgetHost *host);
    void repaintSelection();

    bool isHostSelected(QAbstractWidgetHost *host) const;
    QList<QAbstractWidgetHost*> selectedHosts() const;

    WidgetSelection *addHost(QAbstractWidgetHost *host);
    void removeHost(QAbstractWidgetHost *host);
    QAbstractWidgetHost* current();

    void hide(QAbstractWidgetHost *host);
    void show(QAbstractWidgetHost *host);


    void setCurrent(QAbstractWidgetHost *host);
    void setUndoStack(QUndoStack * undoStack);

protected slots:
    void    hostGeometryChanged();
private:

    typedef QList<WidgetSelection *> SelectionPool;
    SelectionPool m_selectionPool;

    typedef QHash<QAbstractWidgetHost *, WidgetSelection *> SelectionHash;
    SelectionHash m_usedSelections;
    WidgetSelection *       m_current;
    QWidget*                m_formwindow;
    QUndoStack              *m_undoStack;
};

#endif // QSELECTWIDGET_H
