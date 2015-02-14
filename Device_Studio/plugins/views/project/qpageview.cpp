#include "qpageview.h"

#include "qpagepane.h"

#include <QPainter>

QPageView::QPageView(QWidget *parent) :
    QWidget(parent),
    m_select(NULL)
{

}

QPageView::~QPageView()
{

}

void QPageView::addHost(QAbstractWidgetHost *host,int index)
{
    if(m_hostToPane.keys().contains(host))
    {
        return;
    }

    QPagePane *page = new QPagePane(host,this);
    connect(page,SIGNAL(select()),this,SLOT(pagePaneSelect()));
    page->setVisible(true);
    m_pagePaneList.insert(index,page);
    m_hostToPane.insert(host,page);

    calcSize();
}

void QPageView::calcSize()
{
    int w = this->parentWidget()->width();

    w = (w - 40)/3;

    if(w < 100)
    {
        w = 100;
    }

    int i;
    QPagePane * pane;
    for(i = 0; i<m_pagePaneList.size();i++)
    {
        pane = m_pagePaneList.at(i);

        pane->resize(w,w);
        pane->move(10+(w+10)*(i%3),10+(w+10)*(i/3));
    }

    this->resize(2*w+40,10+(w+10)*(i/2+1));
}

void QPageView::resizeEvent(QResizeEvent *)
{
    calcSize();
}

void QPageView::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.fillRect(rect(),QColor(255,255,255));
}

void QPageView::pagePaneSelect()
{
    QPagePane * pane = (QPagePane*)sender();
    if(m_select != NULL)
    {
        m_select->setSelect(false);
    }
    m_select = pane;
    if(m_select != NULL)
    {
        m_select->setSelect(true);
    }
}

void QPageView::setHosts(QList<QAbstractWidgetHost *> hosts)
{
    foreach(QAbstractWidgetHost* host,hosts)
    {
        QPagePane *page = new QPagePane(host,this);
        connect(page,SIGNAL(select()),this,SLOT(pagePaneSelect()));
        page->setVisible(true);
        m_pagePaneList.append(page);
        m_hostToPane.insert(host,page);
    }

    calcSize();
}
