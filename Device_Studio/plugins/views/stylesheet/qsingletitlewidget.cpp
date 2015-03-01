#include "qsingletitlewidget.h"

#include "../../../libs/platform/qtoolbarbutton.h"

#include <QHBoxLayout>
#include <QAction>
#include <QFontMetrics>

QSingleTitleWidget::QSingleTitleWidget(QWidget *parent) :
    QWidget(parent),
    m_text(new QLabel(this))
{

    QAction *ac =new QAction(QIcon(":/inner/images/delete_item.png"),
                             tr("Remove Title"),this);
    connect(ac,SIGNAL(triggered()),this,SIGNAL(remove()));
    m_deleteButton = new QToolBarButton(ac,this);
    m_text->move(0,0);
    m_text->setContentsMargins(4,2,4,2);
    m_text->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    setFixedHeight(22);
    updateWidth();
}

QSingleTitleWidget::~QSingleTitleWidget()
{
}

void QSingleTitleWidget::updateWidth()
{
    QFontMetrics fm(m_text->font());

    int w = fm.width(m_text->text());

    w += 33;
    m_text->setFixedWidth(w);
    setFixedWidth(w);
    m_deleteButton->move(w-26,0);
}

void QSingleTitleWidget::setText(const QString &title)
{
    m_text->setText(title);
    updateWidth();
}
