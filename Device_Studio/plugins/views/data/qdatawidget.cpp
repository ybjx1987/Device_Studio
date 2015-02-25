#include "qdatawidget.h"

#include "qdatalistview.h"
#include "qnewdatagroupdialog.h"
#include "qdeletedatagroupdialog.h"
#include "qnewdatadialog.h"
#include "qdeletedatadialog.h"

#include "../../../libs/kernel/data/qdatagroup.h"
#include "../../../libs/platform/styledbar.h"
#include "../../../libs/platform/propertylist/qpropertylistview.h"
#include "../../../libs/platform/minisplitter.h"
#include "../../../libs/platform/qsoftactionmap.h"
#include "../../../libs/platform/qactiontoolbar.h"
#include "../../../libs/platform/qsoftcore.h"

#include "../../../libs/kernel/data/qabstractdatahost.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/kernel/data/qdatamanager.h"

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

    ac = QSoftActionMap::getAction("Data.Group.Add");
    connect(ac,SIGNAL(triggered()),this,SLOT(newGroup()));

    ac = QSoftActionMap::getAction("Data.Group.Del");
    connect(ac,SIGNAL(triggered()),this,SLOT(delGroup()));

    ac = QSoftActionMap::getAction("Data.Add");
    connect(ac,SIGNAL(triggered()),this,SLOT(newData()));

    ac = QSoftActionMap::getAction("Data.Del");
    connect(ac,SIGNAL(triggered()),this,SLOT(delData()));

    m_project = QSoftCore::getInstance()->getProject();

    connect(m_project,SIGNAL(projectOpened()),
            this,SLOT(projectOpened()));
    connect(m_project,SIGNAL(projectClosed()),
            this,SLOT(projectClosed()));

    updateAction();

    connect(m_dataListview,SIGNAL(updateAction()),
            this,SLOT(updateAction()));

    connect(m_dataListview,SIGNAL(dataSelected(QAbstractDataHost*)),
            this,SLOT(dataSeleted(QAbstractDataHost*)));

    sp->setSizes(QList<int>()<<100<<400);
    m_dataPropertyView->setColumnWidth(0,200);
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

void QDataWidget::newGroup()
{
    QStringList list;

    foreach(QDataGroup * group,m_project->getDataManager()->getGroups())
    {
        list.append(group->getGroupName());
    }

    QNewDataGroupDialog dlg(list,this);

    dlg.exec();

    QString name = dlg.getName();

    if(name != "")
    {
        m_project->getDataManager()->addGroup(name);
    }
}

void QDataWidget::projectClosed()
{
    m_dataListview->clear();
    updateAction();
}

void QDataWidget::projectOpened()
{
    m_dataListview->setDataManager(m_project->getDataManager());
    updateAction();
}

void QDataWidget::updateAction()
{
    QAction *ac;

    if(m_project->getProjectStatus() != PS_OPENED)
    {
        ac = QSoftActionMap::getAction("Data.Group.Add");
        ac->setEnabled(false);
        ac = QSoftActionMap::getAction("Data.Group.Del");
        ac->setEnabled(false);
        ac = QSoftActionMap::getAction("Data.Add");
        ac->setEnabled(false);
        ac = QSoftActionMap::getAction("Data.Del");
        ac->setEnabled(false);
    }
    else
    {
        ac = QSoftActionMap::getAction("Data.Group.Add");
        ac->setEnabled(true);
        if(m_project->getDataManager()->getGroups().size() > 0)
        {
            ac = QSoftActionMap::getAction("Data.Group.Del");
            ac->setEnabled(true);
            ac = QSoftActionMap::getAction("Data.Add");
            ac->setEnabled(true);
        }
        else
        {
            ac = QSoftActionMap::getAction("Data.Group.Del");
            ac->setEnabled(false);
            ac = QSoftActionMap::getAction("Data.Add");
            ac->setEnabled(false);
        }
        int count = 0;
        foreach(QDataGroup * group,m_project->getDataManager()->getGroups())
        {
            count += group->getDatas().size();
        }

        ac = QSoftActionMap::getAction("Data.Del");
        ac->setEnabled(count != 0);
    }
}

void QDataWidget::delGroup()
{
    QDeleteDataGroupDialog dlg(m_project->getDataManager(),this);

    dlg.exec();
}

void QDataWidget::newData()
{
    QNewDataDialog dlg(m_project->getDataManager(),this);

    dlg.exec();
}

void QDataWidget::dataSeleted(QAbstractDataHost *data)
{
    QList<QAbstractProperty*> list;
    if(data != NULL)
    {
        list = data->getPropertys();
        list.removeAll(data->getProperty("objectName"));
        list.removeAll(data->getProperty("type"));
        list.removeAll(data->getProperty("value"));
        list.removeAll(data->getProperty("needSave"));
        list.removeAll(data->getProperty("explanation"));
    }
    m_dataPropertyView->setPropertys(list);
}

void QDataWidget::delData()
{
    QDeleteDataDialog dlg(m_project->getDataManager(),this);

    dlg.exec();
}
