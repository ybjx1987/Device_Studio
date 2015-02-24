#include "qdatawidget.h"

#include "qdatalistview.h"

#include "../../../libs/platform/styledbar.h"
#include "../../../libs/platform/propertylist/qpropertylistview.h"
#include "../../../libs/platform/minisplitter.h"
#include "../../../libs/platform/qsoftactionmap.h"
#include "../../../libs/platform/qactiontoolbar.h"

#include <QVBoxLayout>

QDataWidget::QDataWidget(QWidget * parent):
    QAbstractPageWidget(parent),
    m_dataListview(new QDataListView),
    m_dataListviewBar(new StyledBar),
    m_dataPropertyView(new QPropertyListView),
    m_dataPropertyViewBar(new StyledBar)
{
    initAction();

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

    QActionToolBar *toolBar = new QActionToolBar;

    QList<QAction*> list;

    QAction * ac;

    list.append(QSoftActionMap::getAction("Data.Group.Add"));
    list.append(QSoftActionMap::getAction("Data.Group.Del"));
    ac = new QAction(this);
    ac->setSeparator(true);
    list.append(ac);
    list.append(QSoftActionMap::getAction("Data.Add"));
    list.append(QSoftActionMap::getAction("Data.Del"));
    ac = new QAction(this);
    ac->setSeparator(true);
    list.append(ac);
    toolBar->addButtonActions(list);

    v = new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(toolBar);

    m_dataListviewBar->setLayout(v);
}

void QDataWidget::initAction()
{
    QAction * ac;

    ac = new QAction(QIcon(":/inner/images/add_data_group.png"),tr("Add Group"),this);
    QSoftActionMap::insertAction("Data.Group.Add",ac);

    ac = new QAction(QIcon(":/inner/images/del_data_group.png"),tr("Delete Group"),this);
    QSoftActionMap::insertAction("Data.Group.Del",ac);

    ac = new QAction(QIcon(":/inner/images/del_data.png"),tr("Delete Data"),this);
    QSoftActionMap::insertAction("Data.Del",ac);

    ac = new QAction(QIcon(":/inner/images/add_data.png"),tr("Add Data"),this);
    QSoftActionMap::insertAction("Data.Add",ac);
}
