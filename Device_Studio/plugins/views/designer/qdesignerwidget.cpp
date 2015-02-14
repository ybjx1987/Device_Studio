#include "qdesignerwidget.h"

#include "qwidgetboxlist.h"
#include "formeditor/qformeditor.h"

#include "../../../libs/platform/qactiontoolbar.h"
#include "../../../libs/platform/propertylist/qpropertylistview.h"
#include "../../../libs/platform/styledbar.h"

#include "../../../libs/platform/minisplitter.h"

#include "../../../libs/kernel/host/qhostfactory.h"
#include "../../../libs/kernel/host/qabstracthost.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/kernel/host/qabstractwidgethost.h"

#include "../../../libs/platform/qsoftactionmap.h"

#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>

QDesignerWidget::QDesignerWidget(QWidget * parent ):
    QAbstractPageWidget(parent),
    m_propertyView(new QPropertyListView(this)),
    m_propertyViewBar(new StyledBar(this)),
    m_widgetBoxList(new QWidgetBoxList(this)),
    m_widgetBoxListBar(new StyledBar(this)),
    m_formEditor(new QFormEditor(this)),
    m_formEditorBar(new StyledBar(this)),
    m_currentHost(NULL)
{
    initDesignerViewAction();
    MiniSplitter  *splitter = new MiniSplitter(this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(splitter);
    setLayout(layout);

    QWidget * wid = new QWidget;
    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_widgetBoxListBar);
    layout->addWidget(m_widgetBoxList);
    wid->setLayout(layout);
    splitter->addWidget(wid);

    wid = new QWidget;
    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_formEditorBar);
    layout->addWidget(m_formEditor);
    wid->setLayout(layout);
    splitter->addWidget(wid);

    QHBoxLayout *hl = new QHBoxLayout;
    hl->setMargin(0);
    hl->setSpacing(0);

    m_formlist = new QComboBox;
    m_formlist->setFixedWidth(200);
    hl->addWidget(m_formlist);
    QActionToolBar *toolBar = new QActionToolBar;
    hl->addWidget(toolBar);
    m_formEditorBar->setLayout(hl);

    QList<QAction*>     list;

    list<<QSoftActionMap::getAction("designer.left");
    list<<QSoftActionMap::getAction("designer.right");
    list<<QSoftActionMap::getAction("designer.top");
    list<<QSoftActionMap::getAction("designer.bottom");
    list<<QSoftActionMap::getAction("designer.v-center");
    list<<QSoftActionMap::getAction("designer.h-center");
    QAction * ac = new QAction(this);
    ac->setSeparator(true);
    list<<ac;

    list<<QSoftActionMap::getAction("designer.same-width");
    list<<QSoftActionMap::getAction("designer.same-height");
    list<<QSoftActionMap::getAction("designer.same-rect");
    ac = new QAction(this);
    ac->setSeparator(true);
    list<<ac;

    toolBar->addButtonActions(list);


    wid = new QWidget;
    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_propertyViewBar);
    layout->addWidget(m_propertyView);
    wid->setLayout(layout);
    splitter->addWidget(wid);

    splitter->setStretchFactor(0,0);
    splitter->setStretchFactor(1,1);
    splitter->setStretchFactor(2,0);

    connect(QSoftCore::getInstance()->getProject(),SIGNAL(hostAdded(QAbstractWidgetHost*,int)),
            this,SLOT(formAdded(QAbstractWidgetHost*,int)));

    connect(QSoftCore::getInstance()->getProject(),SIGNAL(projectOpened()),
            this,SLOT(projectOpened()));

    connect(QSoftCore::getInstance()->getProject(),SIGNAL(projectClosed()),
            this,SLOT(projectClosed()));

    connect(m_formEditor,SIGNAL(select(QAbstractWidgetHost*)),
            this,SLOT(hostSelect(QAbstractWidgetHost*)));
}

void QDesignerWidget::formAdded(QAbstractWidgetHost *host, int index)
{
    m_formEditor->setHostList(QList<QAbstractWidgetHost*>()<<host);
    m_formlist->addItem(host->getName());
}

void QDesignerWidget::initDesignerViewAction()
{
    QAction *ac;
    ac=new QAction(QIcon(":/inner/images/left.png"),tr("Left"),NULL);
    QSoftActionMap::insertAction("designer.left",ac);
    ac=new QAction(QIcon(":/inner/images/top.png"),tr("Top"),NULL);
    QSoftActionMap::insertAction("designer.top",ac);
    ac=new QAction(QIcon(":/inner/images/right.png"),tr("Right"),NULL);
    QSoftActionMap::insertAction("designer.right",ac);
    ac=new QAction(QIcon(":/inner/images/bottom.png"),tr("Bottom"),NULL);
    QSoftActionMap::insertAction("designer.bottom",ac);
    ac=new QAction(QIcon(":/inner/images/v-center.png"),tr("Vertically"),NULL);
    QSoftActionMap::insertAction("designer.v-center",ac);
    ac=new QAction(QIcon(":/inner/images/h-center.png"),tr("Horizontally"),NULL);
    QSoftActionMap::insertAction("designer.h-center",ac);
    ac=new QAction(QIcon(":/inner/images/same-width.png"),tr("Same Width"),NULL);
    QSoftActionMap::insertAction("designer.same-width",ac);
    ac=new QAction(QIcon(":/inner/images/same-height.png"),tr("Same Height"),NULL);
    QSoftActionMap::insertAction("designer.same-height",ac);
    ac=new QAction(QIcon(":/inner/images/same-rect.png"),tr("Same Rect"),NULL);
    QSoftActionMap::insertAction("designer.same-rect",ac);
}

void QDesignerWidget::projectOpened()
{
    QProject * project = QSoftCore::getInstance()->getProject();

    QList<QAbstractWidgetHost*> forms = project->getForms();

    m_formEditor->setHostList(forms);
    if(forms.size()>0)
    {
        m_formEditor->showHost(forms.first());
    }
    foreach(QAbstractWidgetHost* host,forms)
    {
        m_formlist->addItem(host->getPropertyValue("objectName").toString());
    }
}

void QDesignerWidget::projectClosed()
{

}

void QDesignerWidget::hostSelect(QAbstractWidgetHost *host)
{
    if(host != m_currentHost)
    {
        m_currentHost = host;
        if(m_currentHost!= NULL)
        {
            m_propertyView->setPropertys(m_currentHost->getPropertys());
            m_formlist->setCurrentText(m_currentHost->getPropertyValue("objectName").toString());
        }
    }
}
