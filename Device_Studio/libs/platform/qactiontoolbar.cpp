#include "qactiontoolbar.h"

#include "qtoolbarbutton.h"

#include <QHBoxLayout>

QActionToolBar::QActionToolBar(QWidget *parent):
    QWidget(parent)
{
    QHBoxLayout *l=new QHBoxLayout();
    l->setContentsMargins(5,0,5,0);
    l->setSpacing(1);
    this->setLayout(l);

    m_spacer = new QSpacerItem(0,0,QSizePolicy::Expanding,
                               QSizePolicy::Expanding);
}

void QActionToolBar::addButtonActions(const QList<QAction*> &actions,
                                      Qt::AlignmentFlag flag)
{
    qDeleteAll(m_buttons);
    m_buttons.clear();
    QToolBarButton *button;
    QLayout *l=this->layout();
    l->removeItem(m_spacer);
    if(flag == Qt::AlignRight)
    {
        ((QBoxLayout*)l)->addSpacerItem(m_spacer);
    }


    for(int i=0;i<actions.size();i++)
    {
        button=new QToolBarButton(actions.at(i),this);
        l->addWidget(button);
        m_buttons.append(button);
    }

    if(flag == Qt::AlignLeft)
    {
        ((QBoxLayout*)l)->addSpacerItem(m_spacer);
    }

    addActions(actions);
}
