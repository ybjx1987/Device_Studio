#include "qresourcewidget.h"

#include "qresourcelistview.h"
#include "qaddresourcedialog.h"

#include "../../../libs/platform/styledbar.h"
#include "../../../libs/platform/minisplitter.h"
#include "../../../libs/platform/qactiontoolbar.h"
#include "../../../libs/kernel/resource/qresourcemanager.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/platform/qbaselistview.h"
#include "../../../libs/platform/qsoftactionmap.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include <QAction>

QResourceWidget::QResourceWidget(QWidget * parent):
    QAbstractPageWidget(parent),
    m_resourceListViewBar(new StyledBar),
    m_resourceListView(new QResourceListView)
{
    registerAction();
    MiniSplitter * sp = new MiniSplitter;

    QVBoxLayout *vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);

    vb->addWidget(m_resourceListViewBar);
    vb->addWidget(m_resourceListView);

    QWidget * wid = new QWidget;

    wid->setLayout(vb);

    sp->addWidget(wid);


    vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);
    vb->addWidget(sp);
    setLayout(vb);

    m_resourceListView->header()->hide();

    updateAction();

    QActionToolBar  *toolBar;

    toolBar = new QActionToolBar;

    QList<QAction*> list;

    list.append(QSoftActionMap::getAction("resource.add"));
    list.append(QSoftActionMap::getAction("resource.del"));
    QAction * ac;
    ac = new QAction(this);
    ac->setSeparator(true);
    list.append(ac);
    toolBar->addButtonActions(list);

    vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);
    vb->addWidget(toolBar);
    m_resourceListViewBar->setLayout(vb);

}

void QResourceWidget::projectOpened()
{
    QProject * project = (QProject*)sender();
    m_resourceListView->init(project->getResourceManager());
    updateAction();
}

void QResourceWidget::projectClosed()
{
    updateAction();
}

void QResourceWidget::registerAction()
{
    QAction * ac;

    ac = new QAction(QIcon(":/inner/images/add.png"),tr("Add Resource"),this);
    connect(ac,SIGNAL(triggered()),this,SLOT(addResource()));
    QSoftActionMap::insertAction("resource.add",ac);

    ac = new QAction(QIcon(":/inner/images/del.png"),tr("Delete Resource"),this);
    QSoftActionMap::insertAction("resource.del",ac);
}

void QResourceWidget::updateAction()
{
    QProject * project = QSoftCore::getInstance()->getProject();

    if(project->getProjectStatus() != PS_OPENED)
    {
        QSoftActionMap::getAction("resource.add")->setEnabled(false);
        QSoftActionMap::getAction("resource.del")->setEnabled(false);
    }
    else
    {
        QSoftActionMap::getAction("resource.add")->setEnabled(true);
        if(project->getResourceManager()->getResources().size() > 0)
        {
            QSoftActionMap::getAction("resource.del")->setEnabled(true);
        }
        else
        {
            QSoftActionMap::getAction("resource.del")->setEnabled(false);
        }
    }
}

void QResourceWidget::addResource()
{
    QAddResourceDialog dlg(this);

    dlg.exec();
}
