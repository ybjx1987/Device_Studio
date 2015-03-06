#include "qstylesheetwidget.h"

#include "qstylesheetgrouplistview.h"

#include "../../../libs/platform/styledbar.h"
#include "../../../libs/platform/minisplitter.h"

#include <QVBoxLayout>

QStyleSheetWidget::QStyleSheetWidget(QWidget *parent) :
    QWidget(parent),
    m_groupListView(new QStyleSheetGroupListView),
    m_groupListViewBar(new StyledBar),
    m_itemWidget(new QStackedWidget),
    m_itemWidgetBar(new StyledBar)
{
    MiniSplitter *sp = new MiniSplitter;

    QWidget * wid = new QWidget;

    QVBoxLayout *vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);
    vb->addWidget(m_groupListViewBar);
    vb->addWidget(m_groupListView);
    wid->setLayout(vb);

    sp->addWidget(wid);

    wid = new QWidget;
    vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);
    vb->addWidget(m_itemWidgetBar);
    vb->addWidget(m_itemWidget);
    wid->setLayout(vb);

    sp->addWidget(wid);

    sp->setStretchFactor(0,0);
    sp->setStretchFactor(1,1);

    vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);
    vb->addWidget(sp);
    setLayout(vb);

}

QStyleSheetWidget::~QStyleSheetWidget()
{

}

