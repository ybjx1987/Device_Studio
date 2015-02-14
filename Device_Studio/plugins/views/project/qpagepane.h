#ifndef QPAGEPANE_H
#define QPAGEPANE_H

#include <QWidget>

class QAbstractWidgetHost;

class QPagePane : public QWidget
{
    Q_OBJECT
public:
    explicit QPagePane(QAbstractWidgetHost * host,QWidget *parent = 0);
    ~QPagePane();

    void    setSelect(bool select);
protected:
    void    paintEvent(QPaintEvent *);
    void    mouseReleaseEvent(QMouseEvent *);
    void    mouseDoubleClickEvent(QMouseEvent *);
signals:
    void    select();
    void    doubleClick();
public slots:
protected:
    QAbstractWidgetHost     *m_host;
    bool                    m_select;
};

#endif // QPAGEPANE_H
