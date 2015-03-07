#include "qsingletitlewidget.h"

#include "../../../libs/platform/qtoolbarbutton.h"

#include <QHBoxLayout>
#include <QAction>
#include <QFontMetrics>
#include <QPainter>

QSingleTitleWidget::QSingleTitleWidget(const QString & title,QWidget *parent) :
    QWidget(parent),
    m_text(new QLabel(this))
{

    QAction *ac =new QAction(QIcon(":/inner/images/delete_item.png"),
                             tr("Remove Title"),this);
    connect(ac,SIGNAL(triggered()),this,SIGNAL(remove()));
    m_deleteButton = new QToolBarButton(ac,this);
    m_text->move(0,0);
    m_text->setText(title);
    m_text->setContentsMargins(4,2,4,2);
    m_text->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_text->setFixedHeight(22);
    setFixedHeight(22);
    updateWidth();
}

QSingleTitleWidget::~QSingleTitleWidget()
{
}

void QSingleTitleWidget::updateWidth()
{
    int w = m_text->sizeHint().width();

    w += 22;
    if(w < 40)
    {
        w=40;
    }
    m_text->setFixedWidth(w);
    setFixedWidth(w);
    m_deleteButton->move(w-26,0);
}

QString QSingleTitleWidget::text()
{
    return m_text->text();
}

void QSingleTitleWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.setPen(QColor(192,192,192));
    p.drawLine(width()-2,0,width()-2,height());
    p.setPen(QColor(255,255,255));
    p.drawLine(width()-1,0,width()-1,height());
}
