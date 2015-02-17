#include "qfancytabviewwidget.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include <QIcon>

static void drawSeparator(QPainter *painter, QPoint top, QPoint bottom)
{
    QLinearGradient grad(top, bottom);
    grad.setColorAt(0, QColor(255, 255, 255, 20));
    grad.setColorAt(0.4, QColor(255, 255, 255, 60));
    grad.setColorAt(0.7, QColor(255, 255, 255, 50));
    grad.setColorAt(1, QColor(255, 255, 255, 40));
    painter->setPen(QPen(grad, 0));
    painter->drawLine(top, bottom);
    grad.setColorAt(0, QColor(0, 0, 0, 30));
    grad.setColorAt(0.4, QColor(0, 0, 0, 70));
    grad.setColorAt(0.7, QColor(0, 0, 0, 70));
    grad.setColorAt(1, QColor(0, 0, 0, 40));
    painter->setPen(QPen(grad, 0));
    painter->drawLine(top - QPoint(1,0), bottom - QPoint(1,0));
}

QFancyTabViewWidget::QFancyTabViewWidget(QWidget *parent) :
    QWidget(parent),
    m_select(false),
    m_iconLabel(new QLabel(this)),
    m_textLabel(new QLabel(this))
{
    select(false);

    m_iconLabel->setFixedSize(QSize(16,16));

    QHBoxLayout *h= new QHBoxLayout;
    h->setContentsMargins(5,0,5,0);
    h->setSpacing(5);
    h->addWidget(m_iconLabel);
    h->addWidget(m_textLabel,1);
    setLayout(h);
}

QFancyTabViewWidget::~QFancyTabViewWidget()
{

}

void QFancyTabViewWidget::enterEvent(QEvent *)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
    animation->setDuration(125);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void QFancyTabViewWidget::leaveEvent(QEvent *)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
    animation->setDuration(125);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void QFancyTabViewWidget::mouseReleaseEvent(QMouseEvent *)
{
    if(!m_select)
    {
        emit selected();
    }
}

void QFancyTabViewWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if(m_select)
    {
        p.save();
        QLinearGradient grad(QPoint(0, 0), QPoint(0, rect().height() - 1));
        grad.setColorAt(0, QColor(247, 247, 247));
        grad.setColorAt(1, QColor(205, 205, 205));
        p.fillRect(rect(),grad);
        p.restore();
    }
    else
    {
        if (m_fader > 0)
        {
            p.save();
            int fader = int(40 * m_fader);
            p.fillRect(rect(),QColor(120,120,120,80).lighter(100+fader*2));
            p.restore();
        }
    }

    drawSeparator(&p,rect().topRight(),rect().bottomRight());

    QWidget::paintEvent(e);
}

void QFancyTabViewWidget::setFader(float fader)
{
    m_fader = fader;
    update();
}

float QFancyTabViewWidget::fader()
{
    return m_fader;
}

void QFancyTabViewWidget::select(bool select)
{
    m_select = select;
    this->update();
    if(m_select)
    {
        setStyleSheet("color:rgb(0,0,0);");
    }
    else
    {
        setStyleSheet("color:rgb(255,255,255);");
    }
}

void QFancyTabViewWidget::setIcon(const QString &icon)
{
    QIcon ic(icon);
    if(ic.isNull())
    {
        m_iconLabel->setVisible(false);
    }
    else
    {
        m_iconLabel->setPixmap(ic.pixmap(QSize(16,16)));
    }
}

void QFancyTabViewWidget::setText(const QString &text)
{
    m_textLabel->setText(text);

    QFontMetrics ms(font());

    int w = ms.width(text);

    setFixedWidth(w+40);
}

QString QFancyTabViewWidget::getText()
{
    return m_textLabel->text();
}
