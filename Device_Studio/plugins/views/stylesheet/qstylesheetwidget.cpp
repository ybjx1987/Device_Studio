#include "qstylesheetwidget.h"

#include "qstylesheetgrouplistview.h"
#include "qonegroupwidget.h"
#include "qdeletestylesheetdialog.h"
#include "qnewstylesheetgroupdialog.h"
#include "qnewstylesheetitemdialog.h"

#include "../../../libs/platform/styledbar.h"
#include "../../../libs/platform/minisplitter.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/platform/qsoftactionmap.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/kernel/stylesheet/qstylesheetmanager.h"
#include "../../../libs/kernel/stylesheet/qstylesheetgroup.h"
#include "../../../libs/platform/qactiontoolbar.h"

#include <QVBoxLayout>
#include <QAction>

QStyleSheetWidget::QStyleSheetWidget(QWidget *parent) :
    QAbstractPageWidget(parent),
    m_groupListView(new QStyleSheetGroupListView),
    m_groupListViewBar(new StyledBar),
    m_itemWidget(new QStackedWidget),
    m_itemWidgetBar(new StyledBar)
{
    initAction();
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

    connect(m_groupListView,SIGNAL(groupSelect(QStyleSheetGroup*)),
            this,SLOT(groupSelected(QStyleSheetGroup*)));

    QActionToolBar * toolBar;
    QList<QAction*> list;

    QAction * ac;

    ac = QSoftActionMap::getAction("StyleSheet.Group.Add");
    connect(ac,SIGNAL(triggered()),this,SLOT(newGroup()));
    list.append(ac);

    ac = QSoftActionMap::getAction("StyleSheet.Group.Del");
    connect(ac,SIGNAL(triggered()),this,SLOT(delGroup()));
    list.append(ac);

    ac = new QAction(this);
    ac->setSeparator(true);
    list.append(ac);

    ac = QSoftActionMap::getAction("StyleSheet.Add");
    connect(ac,SIGNAL(triggered()),this,SLOT(newItem()));
    list.append(ac);

    ac = new QAction(this);
    ac->setSeparator(true);
    list.append(ac);

    toolBar = new QActionToolBar;
    toolBar->addButtonActions(list);

    vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);
    vb->addWidget(toolBar);
    m_groupListViewBar->setLayout(vb);



    updateAction();
}

QStyleSheetWidget::~QStyleSheetWidget()
{

}

void QStyleSheetWidget::projectOpened()
{
    QStyleSheetManager * manager = QSoftCore::getInstance()->getProject()
            ->getStyleSheetManager();
    foreach(QStyleSheetGroup * group,manager->getGroups())
    {
        addGroup(group);
    }

    m_groupListView->init(manager);

    connect(manager,SIGNAL(groupAdded(QStyleSheetGroup*)),
            this,SLOT(groupAdded(QStyleSheetGroup*)));
    connect(manager,SIGNAL(groupDeled(QStyleSheetGroup*)),
            this,SLOT(groupDeled(QStyleSheetGroup*)));

    updateAction();
}

void QStyleSheetWidget::projectClosed()
{
    m_groupListView->clear();
    m_groupToWidget.clear();
    foreach(QWidget * wid,m_widgetToGroup.keys())
    {
        m_itemWidget->removeWidget(wid);
    }
    qDeleteAll(m_widgetToGroup.keys());
    m_widgetToGroup.clear();

    updateAction();
}

void QStyleSheetWidget::addGroup(QStyleSheetGroup *group)
{
    QOneGroupWidget * wid = new QOneGroupWidget(group);

    m_itemWidget->addWidget(wid);

    m_groupToWidget.insert(group,wid);
    m_widgetToGroup.insert(wid,group);
}

void QStyleSheetWidget::groupSelected(QStyleSheetGroup *group)
{
    QOneGroupWidget * wid = m_groupToWidget.value(group);
    if(wid != NULL)
    {
        m_itemWidget->setCurrentWidget(wid);
    }
    else
    {
        m_itemWidget->setCurrentIndex(-1);
    }
}

void QStyleSheetWidget::initAction()
{
    QAction * ac;

    ac = new QAction(QIcon(":/inner/images/add_data_group.png"),tr("Add Group"),this);
    QSoftActionMap::insertAction("StyleSheet.Group.Add",ac);

    ac = new QAction(QIcon(":/inner/images/del_data_group.png"),tr("Delete Group"),this);
    QSoftActionMap::insertAction("StyleSheet.Group.Del",ac);

    ac = new QAction(QIcon(":/inner/images/add_data.png"),tr("Add Data"),this);
    QSoftActionMap::insertAction("StyleSheet.Add",ac);
}

void QStyleSheetWidget::updateAction()
{
    QProject * project = QSoftCore::getInstance()->getProject();

    bool opened = (project->getProjectStatus() == PS_OPENED);
    bool hasGroup = false;
    if(opened)
    {
        hasGroup = project->getStyleSheetManager()->getGroups().size()>0;
    }

    QSoftActionMap::getAction("StyleSheet.Group.Add")->setEnabled(opened);
    QSoftActionMap::getAction("StyleSheet.Group.Del")->setEnabled(opened && hasGroup);
    QSoftActionMap::getAction("StyleSheet.Add")->setEnabled(opened && hasGroup);
}

void QStyleSheetWidget::newGroup()
{
    QProject * project = QSoftCore::getInstance()->getProject();
    QNewStyleSheetGroupDialog dlg(project->getStyleSheetManager()->getGroupNames(),this);

    dlg.exec();

    QString name = dlg.getName();

    if(name != "")
    {
        project->getStyleSheetManager()->addGroup(name);
    }
}

void QStyleSheetWidget::delGroup()
{
    QDeleteStyleSheetDialog dlg(this);

    dlg.init(QSoftCore::getInstance()->getProject()->getStyleSheetManager());

    dlg.exec();
}

void QStyleSheetWidget::groupAdded(QStyleSheetGroup *group)
{
    m_groupListView->groupAdded(group);
    addGroup(group);
    updateAction();
}

void QStyleSheetWidget::groupDeled(QStyleSheetGroup *group)
{
    m_groupListView->groupDeled(group);

    if(m_groupToWidget.keys().contains(group))
    {
        QOneGroupWidget * wid = m_groupToWidget.value(group);

        m_widgetToGroup.remove(wid);
        m_groupToWidget.remove(group);

        delete wid;
    }

    updateAction();
}

void QStyleSheetWidget::newItem()
{
    QNewStyleSheetItemDialog dlg(QSoftCore::getInstance()->getProject()
                                 ->getStyleSheetManager(),this);

    dlg.exec();
}
