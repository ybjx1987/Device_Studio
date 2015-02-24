#include "qdatawidget.h"

#include "qdatalistview.h"

#include "../../../libs/platform/styledbar.h"
#include "../../../libs/platform/propertylist/qpropertylistview.h"
#include "../../../libs/platform/minisplitter.h"

#include <QVBoxLayout>

QDataWidget::QDataWidget(QWidget * parent):
    QAbstractPageWidget(parent),
    m_dataListview(new QDataListView),
    m_dataListviewBar(new StyledBar),
    m_dataPropertyView(new QPropertyListView),
    m_dataPropertyViewBar(new StyledBar)
{

    QWidget * wid;
    QVBoxLayout *v;
    MiniSplitter    *sp = new MiniSplitter;

    wid = new QWidget;
    v = new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(m_dataListviewBar);
    v->addWidget(m_dataListview);
    wid->setLayout(v);
    sp->addWidget(wid);

    wid = new QWidget;
    v = new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(m_dataPropertyViewBar);
    v->addWidget(m_dataPropertyView);
    wid->setLayout(v);
    sp->addWidget(wid);

    v = new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(sp);

    sp->setStretchFactor(0,1);
    sp->setStretchFactor(1,0);

    setLayout(v);
}
