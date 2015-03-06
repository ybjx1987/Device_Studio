#include "qitemendwidget.h"

#include "../../../libs/platform/stylehelper.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QSpacerItem>
#include <QPainter>

QItemEndWidget::QItemEndWidget(QWidget *parent) :
    QWidget(parent)
{
    QWidget * wid = new QWidget;
    wid->setStyleSheet("background-image:url(:/inner/images/end.png);"
                       "background-repeat:no-repeat;"
                       "background-position:center;");
    wid->setFixedSize(22,22);

    QHBoxLayout *hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(0);
    hb->addWidget(wid);
    hb->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Expanding));
    setLayout(hb);
    setFixedHeight(22);
}

QItemEndWidget::~QItemEndWidget()
{

}

void QItemEndWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    StyleHelper::horizontalGradient(&p,rect(),rect(),true);
    p.setPen(QColor(128,128,128));
    p.drawLine(0,height()-1,width()-1,height()-1);
}
