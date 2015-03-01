#include "qstylesheetwidget.h"

#include "qnewstylesheetgroupdialog.h"
#include "qstylesheetgrouplistview.h"
#include "qdeletestylesheetdialog.h"

#include "../../../libs/kernel/qproject.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/platform/minisplitter.h"
#include "../../../libs/platform/styledbar.h"
#include "../../../libs/platform/qsoftactionmap.h"
#include "../../../libs/platform/qactiontoolbar.h"
#include "../../../libs/kernel/stylesheet/qstylesheetmanager.h"

#include <QVBoxLayout>
#include <QScrollArea>

QStyleSheetWidget::QStyleSheetWidget(QWidget * parent):
    QAbstractPageWidget(parent),
    m_groupView(new QStyleSheetGroupListView(this)),
    m_groupViewBar(new StyledBar(this))
{
    initAction();

    MiniSplitter * sp = new MiniSplitter;
    QVBoxLayout * vb;
    QWidget * wid;

    wid = new QWidget;
    vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);
    vb->addWidget(m_groupViewBar);
    vb->addWidget(m_groupView);
    wid->setLayout(vb);
    sp->addWidget(wid);


    vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);
    vb->addWidget(sp);
    setLayout(vb);

    connect(QSoftCore::getInstance()->getProject(),SIGNAL(projectOpened()),
            this,SLOT(projectOpened()));
    connect(QSoftCore::getInstance()->getProject(),SIGNAL(projectClosed()),
            this,SLOT(projectClosed()));

    QActionToolBar * toolbar;

    QList<QAction*> list;

    toolbar = new QActionToolBar;
    vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);
    vb->addWidget(toolbar);
    m_groupViewBar->setLayout(vb);
    list.append(QSoftActionMap::getAction("stylesheet.group.add"));
    list.append(QSoftActionMap::getAction("stylesheet.group.del"));
    toolbar->addButtonActions(list);
    updateAction();

    connect(m_groupView,SIGNAL(updateAction()),
            this,SLOT(updateAction()));
}

void QStyleSheetWidget::projectOpened()
{
    QProject * project = QSoftCore::getInstance()->getProject();

    m_groupView->init(project->getStyleSheetManager());

    updateAction();
}

void QStyleSheetWidget::projectClosed()
{
    m_groupView->clear();

    updateAction();
}

void QStyleSheetWidget::initAction()
{
    QAction * ac;

    ac= new QAction(QIcon(":/inner/images/add_data_group.png"),tr("Add style sheet group"),this);
    QSoftActionMap::insertAction("stylesheet.group.add",ac);
    connect(ac,SIGNAL(triggered()),this,SLOT(newGroup()));

    ac= new QAction(QIcon(":/inner/images/del_data_group.png"),tr("Add style sheet group"),this);
    QSoftActionMap::insertAction("stylesheet.group.del",ac);
    connect(ac,SIGNAL(triggered()),this,SLOT(delGroup()));
}

void QStyleSheetWidget::updateAction()
{
    QProject * project = QSoftCore::getInstance()->getProject();

    if(project->getProjectStatus() == PS_OPENED)
    {
        QSoftActionMap::getAction("stylesheet.group.add")->setEnabled(true);
        if(project->getStyleSheetManager()->getGroups().size()>0)
        {
            QSoftActionMap::getAction("stylesheet.group.del")->setEnabled(true);
        }
        else
        {
            QSoftActionMap::getAction("stylesheet.group.del")->setEnabled(false);
        }
    }
    else
    {
        QSoftActionMap::getAction("stylesheet.group.add")->setEnabled(false);
        QSoftActionMap::getAction("stylesheet.group.del")->setEnabled(false);
    }
}

void QStyleSheetWidget::newGroup()
{

    QStyleSheetManager * manager = QSoftCore::getInstance()->getProject()
            ->getStyleSheetManager();
    QNewStyleSheetGroupDialog dlg(manager->getGroupNames(),this);
    dlg.exec();

    QString name = dlg.getName();
    if(name != "")
    {
        manager->addGroup(name);
    }
}

void QStyleSheetWidget::delGroup()
{
    QDeleteStyleSheetDialog dlg(this);

    dlg.init(QSoftCore::getInstance()->getProject()
             ->getStyleSheetManager());

    dlg.exec();
}
