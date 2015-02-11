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

protected:
    void    paintEvent(QPaintEvent *);

signals:

public slots:
protected:
    QAbstractWidgetHost     *m_host;
};

#endif // QPAGEPANE_H
