#include "qprojectwidget.h"

#include "qpageview.h"

#include "../../../libs/platform/styledbar.h"
#include "../../../libs/platform/propertylist/qpropertylistview.h"
#include "../../../libs/platform/minisplitter.h"

#include "../../../libs/kernel/qproject.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/kernel/host/qprojecthost.h"

#include <QVBoxLayout>
#include <QScrollArea>

QProjectWidget::QProjectWidget(QWidget * parent):
    QAbstractPageWidget(parent),
    m_projectPropertyView(new QPropertyListView(this)),
    m_projectBar(new StyledBar(this)),
    m_pageView(new QPageView(this)),
    m_pageViewBar(new StyledBar(this))
{
    QVBoxLayout *vl = new QVBoxLayout;

    MiniSplitter *sp = new MiniSplitter;

    vl->setMargin(0);
    vl->addWidget(sp);
    setLayout(vl);

    QWidget* wid = new QWidget;

    sp->addWidget(wid);

    vl = new QVBoxLayout;
    vl->setMargin(0);
    vl->setSpacing(0);
    vl->addWidget(m_projectBar);
    vl->addWidget(m_projectPropertyView);
    wid->setLayout(vl);

    QScrollArea * pagePane = new QScrollArea;
    pagePane->setWidget(m_pageView);
    pagePane->setFrameStyle(QFrame::NoFrame);
    pagePane->viewport()->setStyleSheet("background-color:rgb(255,255,255);");

    wid = new QWidget;
    vl = new QVBoxLayout;
    vl->setMargin(0);
    vl->setSpacing(0);
    vl->addWidget(m_pageViewBar);
    vl->addWidget(pagePane);
    wid->setLayout(vl);

    sp->addWidget(wid);

    sp->setStretchFactor(0,0);
    sp->setStretchFactor(1,1);

    connect(QSoftCore::getInstance()->getProject(),SIGNAL(hostAdded(QAbstractWidgetHost*,int)),
            m_pageView,SLOT(addHost(QAbstractWidgetHost*,int)));

    connect(QSoftCore::getInstance()->getProject(),SIGNAL(projectOpened()),
            this,SLOT(projectOpened()));
}

void QProjectWidget::projectOpened()
{
    QProject * project = (QProject*)sender();
    QProjectHost * host = project->getProjectHost();

    m_projectPropertyView->setPropertys(host->getPropertys());

    QList<QAbstractWidgetHost*> forms = project->getForms();

    m_pageView->setHosts(forms);
}
