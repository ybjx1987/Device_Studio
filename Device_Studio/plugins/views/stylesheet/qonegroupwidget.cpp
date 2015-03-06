#include "qonegroupwidget.h"

#include <QPainter>

QOneGroupWidget::QOneGroupWidget(QStyleSheetGroup * group,QWidget *parent) :
    QWidget(parent),
    m_group(group)
{

}

QOneGroupWidget::~QOneGroupWidget()
{

}

void QOneGroupWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.fillRect(rect(),QColor(255,255,255));
}
