#include "qpageview.h"

#include "qpagepane.h"

#include <QPainter>

QPageView::QPageView(QWidget *parent) : QWidget(parent)
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

    page->setVisible(true);
    m_pagePaneList.insert(index,page);
    m_hostToPane.insert(host,page);

    calcSize();
}

void QPageView::calcSize()
{
    int w = this->parentWidget()->width();

    w = (w - 40)/2;

    if(w < 200)
    {
        w = 200;
    }

    int i;
    QPagePane * pane;
    for(i = 0; i<m_pagePaneList.size();i++)
    {
        pane = m_pagePaneList.at(i);

        pane->resize(w,w);
        pane->move(10+(w+10)*(i%2),10+(w+10)*(i/2));
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
