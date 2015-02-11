#ifndef QPAGEVIEW_H
#define QPAGEVIEW_H

#include <QWidget>
#include <QMap>

class QAbstractWidgetHost;
class QPagePane;

class QPageView : public QWidget
{
    Q_OBJECT
public:
    explicit QPageView(QWidget *parent = 0);
    ~QPageView();
public slots:
    void addHost(QAbstractWidgetHost* host,int index);

protected:
    void    calcSize();
    void    resizeEvent(QResizeEvent *);
    void    paintEvent(QPaintEvent *);
signals:

public slots:

protected:
    QList<QPagePane*>       m_pagePaneList;

    QMap<QAbstractWidgetHost*,QPagePane*>   m_hostToPane;
};

#endif // QPAGEVIEW_H
