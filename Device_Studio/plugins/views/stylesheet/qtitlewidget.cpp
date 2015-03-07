#include "qtitlewidget.h"

#include "qsingletitlewidget.h"

#include "../../../libs/platform/qtoolbarbutton.h"
#include "../../../libs/platform/stylehelper.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QAction>
#include <QIcon>
#include <QPainter>

QTitleWidget::QTitleWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hl = new QHBoxLayout;
    hl->setMargin(0);
    hl->setSpacing(0);
    setObjectName("titleWidget");
    QLabel * label = new QLabel;
    QImage image(":/inner/images/begin.png");
    label->setPixmap(QPixmap::fromImage(image));
    label->setFixedSize(16,16);
    QAction * ac = new QAction(QIcon(":/inner/images/add.png"),tr("Add Item"),this);
    m_addButton = new QToolBarButton(ac);
    ac = new QAction(QIcon(":/inner/images/add.png"),tr("Add Item"),this);
    m_addTitleButton = new QToolBarButton(ac);
    m_addTitleButton->setVisible(true);
    hl->addWidget(m_addTitleButton);
    hl->addWidget(label);
    hl->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,
                                      QSizePolicy::Expanding));
    hl->addWidget(m_addButton);
    setLayout(hl);

    setStyleSheet("#titleWidget{background-color:rgb(255,220,180);}");
    setFixedHeight(22);

    connect(m_addTitleButton,SIGNAL(clicked()),this,SIGNAL(addTitle()));
}

QTitleWidget::~QTitleWidget()
{
    clear();
}

void QTitleWidget::addTitle(const QString &title)
{
    if(title == "" || m_textToTitle.keys().contains(title))
    {
        return;
    }

    QSingleTitleWidget * wid = new QSingleTitleWidget(title,this);
    wid->setVisible(true);
    QHBoxLayout *l = (QHBoxLayout*)layout();
    l->insertWidget(l->count()-4,wid);
    m_titles.append(wid);
    m_textToTitle.insert(title,wid);
    connect(wid,SIGNAL(remove()),this,SLOT(titleDeled()));
}

void QTitleWidget::removeTitle(const QString &title)
{
    if(m_textToTitle.keys().contains(title))
    {
        QSingleTitleWidget * wid = m_textToTitle.value(title);

        m_textToTitle.remove(title);
        m_titles.removeAll(wid);
        delete wid;
    }
}

void QTitleWidget::titleDeled()
{
    QSingleTitleWidget *wid=(QSingleTitleWidget*)sender();
    emit delTitle(wid->text());
}

void QTitleWidget::clear()
{
    qDeleteAll(m_titles);
    m_titles.clear();
    m_textToTitle.clear();
}

void QTitleWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    StyleHelper::horizontalGradient(&p,rect(),rect(),true);
    p.setPen(QColor(128,128,128));
    p.drawLine(0,height()-1,width()-1,height()-1);
}
