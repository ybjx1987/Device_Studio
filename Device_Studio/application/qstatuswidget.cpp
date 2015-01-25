#include "qstatuswidget.h"

#include <QHBoxLayout>
#include <QApplication>
#include <QAction>
#include <QPainter>

QString buttonSheet="QToolButton { border-image: url(:/inner/images/panel_button.png) 2 2 2 19;"
" border-width: 2px 2px 2px 19px; padding-left: -17; padding-right: 4 } "
"QToolButton:checked { border-image: url(:/inner/images/panel_button_checked.png) 2 2 2 19 } "
"QToolButton::menu-indicator { width:0; height:0 }"
"QToolButton:checked:hover { border-image: url(:/inner/images/panel_button_checked_hover.png) 2 2 2 19 } "
"QToolButton:pressed:hover { border-image: url(:/inner/images/panel_button_pressed.png) 2 2 2 19 } "
"QToolButton:disabled { border-image: url(:/inner/images/panel_button_pressed.png) 2 2 2 19 } "
"QToolButton:hover { border-image: url(:/inner/images/panel_button_hover.png) 2 2 2 19 } ";

QStatusButton::QStatusButton(int number,const QString &text,QWidget *parent):
    QToolButton(parent),
    m_number(QString::number(number)),
    m_text(text),
    m_flashTimer(new QTimeLine(1000,this))
{
    setFocusPolicy(Qt::NoFocus);
    setCheckable(true);
    QFont fnt=QApplication::font();
    setFont(fnt);

    setStyleSheet(buttonSheet);

    m_flashTimer->setDirection(QTimeLine::Forward);
    m_flashTimer->setCurveShape(QTimeLine::SineCurve);
    m_flashTimer->setFrameRange(0,92);
    connect(m_flashTimer,SIGNAL(valueChanged(qreal)),this,SLOT(update()));
    connect(m_flashTimer,SIGNAL(finished()),this,SLOT(update()));

    m_label=new QLabel(this);
    fnt.setBold(true);
    fnt.setPixelSize(11);
    m_label->setFont(fnt);
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setStyleSheet("background-color:#818181;color:white;border-radius:6px;padding-left:4px;padding:4px;");
    m_label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_label->hide();
}

QSize QStatusButton::sizeHint()const
{
    ensurePolished();

    QSize s=fontMetrics().size(Qt::TextSingleLine,m_text);
    s.rwidth()+=19+5+2;
    s.rheight()+=2+2;

    if(!m_label->text().isNull())
    {
        s.rwidth()+=m_label->width();
    }
    return s.expandedTo(QApplication::globalStrut());
}

void QStatusButton::resizeEvent(QResizeEvent *e)
{
    QToolButton::resizeEvent(e);
    if(!m_label->text().isNull())
    {
        m_label->move(width()-m_label->width()-3,(height()-m_label->height()+1)/2);
        m_label->show();
    }
}

void QStatusButton::paintEvent(QPaintEvent *e)
{
    QToolButton::paintEvent(e);
    const QFontMetrics fm=fontMetrics();
    const int baseLine=(height()-fm.height()+1)/2+fm.ascent();
    const int numberWidth=fm.width(m_number);

    QPainter p(this);
    if(m_flashTimer->state()==QTimeLine::Running)
    {
        p.setPen(Qt::transparent);
        p.fillRect(rect().adjusted(19,1,-1,-1),QBrush(QColor(255,0,0,m_flashTimer->currentFrame())));
    }
    p.setFont(font());
    p.setPen(Qt::white);
    p.drawText((20-numberWidth)/2,baseLine,m_number);
    if(!isChecked())
    {
        p.setPen(Qt::black);
    }
    int leftPart=22;
    int labelWidth=m_label->isVisible()?m_label->width()+3:0;
    p.drawText(leftPart,baseLine,fm.elidedText(m_text,Qt::ElideRight,width()-leftPart-1-labelWidth));
}

void QStatusButton::checkStateSet()
{
    QToolButton::checkStateSet();
    m_flashTimer->stop();

    if(isChecked())
    {
        m_label->setStyleSheet("background-color:#e1e1e1;color:#606060;border-radius:6px;padding-left:4px;padding-right:4px;");
    }
    else
    {
        m_label->setStyleSheet("background-color:#818181;color:white;border-radius:6px;padding-left:4px;padding-right:4px;");
    }
}

void QStatusButton::flash(int count)
{
    setVisible(true);
    if(!isChecked())
    {
        m_flashTimer->setLoopCount(count);
        if(m_flashTimer->state()!=QTimeLine::Running)
        {
            m_flashTimer->start();
        }
        update();
    }
}

void QStatusButton::setIconBadgeNumber(int number)
{
    if(number)
    {
        const QString text=QString::number(number);
        m_label->setText(text);

        QSize size=m_label->sizeHint();
        if(size.height()<size.height())
        {
            size.setWidth(size.height()+((size.width()-size.height())&1));
        }
        m_label->resize(size);
    }
    else
    {
        m_label->setText(QString());
        m_label->hide();
    }
    updateGeometry();
}

QStatusWidget::QStatusWidget(QWidget *parent) :
    QWidget(parent)
{

    QHBoxLayout *h=new QHBoxLayout;
    h->setContentsMargins(5,1,0,0);
    h->setSpacing(4);
    this->setLayout(h);


    QStatusButton * button;

    button=new QStatusButton(1,tr("Output"),this);
    h->addWidget(button,0,Qt::AlignLeft);
    connect(button,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    m_buttons.append(button);

    h->addWidget(new QWidget,1);

    m_select=-1;
}

void QStatusWidget::buttonClicked()
{
    QStatusButton* button=qobject_cast<QStatusButton*>(sender());
    int index=m_buttons.indexOf(button);
    if(index!=-1)
    {
        if(index!=m_select)
        {
            if(m_select!=-1)
            {
                emit clicked(m_select,false);
                m_buttons.at(m_select)->setChecked(false);
            }
            m_select=index;
            m_buttons.at(m_select)->setChecked(true);
            emit clicked(m_select,true);

        }
        else
        {
            emit clicked(m_select,false);
            m_select=-1;
        }
    }
}

void QStatusWidget::setButtonEnabled(int index, bool enabled)
{
    if(index<0 || index>=m_buttons.size())
    {
        return;
    }
    m_buttons.at(index)->setEnabled(enabled);
    m_buttons.at(index)->checkStateSet();
}

void QStatusWidget::setButtonChecked(int index, bool checked)
{
     if(checked && m_select!=index)
     {
         if(m_select!=-1)
         {
             emit clicked(m_select,false);
             m_buttons.at(m_select)->setChecked(false);
         }
         m_select=index;
         m_buttons.at(m_select)->setChecked(true);
         emit clicked(m_select,true);
     }
     else if(!checked && m_select==index)
     {
         emit clicked(m_select,false);
         m_buttons.at(m_select)->setChecked(false);
         m_select=-1;
     }
}

