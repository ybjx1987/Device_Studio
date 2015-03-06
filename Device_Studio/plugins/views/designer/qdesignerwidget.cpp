#include "qdesignerwidget.h"

#include "qwidgetboxlist.h"
#include "formeditor/qformeditor.h"
#include "qhostlistview.h"

#include "../../../libs/platform/qactiontoolbar.h"
#include "../../../libs/platform/propertylist/qpropertylistview.h"
#include "../../../libs/platform/styledbar.h"

#include "../../../libs/platform/qlanguageid.h"
#include "../../../libs/platform/minisplitter.h"
#include "../../../libs/kernel/language/qlanguagemanager.h"
#include "../../../libs/kernel/language/qlanguage.h"
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
    m_formEditorBar(new StyledBar(this)),
    m_hostListView(new QHostListView(this)),
    m_hostListViewBar(new StyledBar(this)),
    m_currentHost(NULL),
    m_languageList(new QComboBox(this))
{
    initDesignerViewAction();
    m_formEditor = new QFormEditor(this);
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
    hl->addWidget(m_languageList);
    m_languageList->setFixedWidth(100);
    QActionToolBar *toolBar = new QActionToolBar;
    hl->addWidget(toolBar,1);
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

    MiniSplitter *sp = new MiniSplitter(Qt::Vertical);
    wid = new QWidget;
    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_propertyViewBar);
    layout->addWidget(m_propertyView);
    wid->setLayout(layout);
    sp->addWidget(wid);
    wid = new QWidget;
    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_hostListViewBar);
    layout->addWidget(m_hostListView);
    wid->setLayout(layout);
    sp->addWidget(wid);
    splitter->addWidget(sp);

    splitter->setStretchFactor(0,0);
    splitter->setStretchFactor(1,1);
    splitter->setStretchFactor(2,0);

    connect(QSoftCore::getInstance()->getProject(),SIGNAL(hostAdded(QAbstractWidgetHost*,int)),
            this,SLOT(formAdded(QAbstractWidgetHost*,int)));

    connect(m_formEditor,SIGNAL(select(QAbstractWidgetHost*)),
            this,SLOT(hostSelect(QAbstractWidgetHost*)));
    m_hostListView->setHost(NULL);


    connect(m_formEditor,SIGNAL(formSelect(QAbstractWidgetHost*)),
            this,SLOT(formSelect(QAbstractWidgetHost*)));
    connect(m_hostListView,SIGNAL(hostSelectChanged(QAbstractWidgetHost*)),
            this,SLOT(hostSelect(QAbstractWidgetHost*)));

    connect(m_languageList,SIGNAL(currentIndexChanged(int)),
            this,SLOT(selectLanguage()));
}

void QDesignerWidget::formAdded(QAbstractWidgetHost *host, int)
{
    m_formEditor->setHostList(QList<QAbstractWidgetHost*>()<<host);
    m_formlist->addItem(host->getPropertyValue("objectName").toString());
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
    m_languageList->clear();
    foreach(QLanguage * language,project->getLanguageManager()->getLanguages())
    {
        QLanguageInfo info = QLanguageID::getLanguageInfo(language->getID());
        m_languageList->addItem(QIcon(info.m_icon),info.m_name,info.m_id);
    }
    QLanguage * language = project->getLanguageManager()->getCurrentLanguage();

    if(language != NULL)
    {
        m_languageList->setCurrentText(QLanguageID::getLanguageInfo(language->getID()).m_name);
    }
    else
    {
        m_languageList->setCurrentIndex(-1);
    }
}

void QDesignerWidget::projectClosed()
{
    m_formEditor->clear();
    m_formlist->clear();
    m_languageList->clear();
}

void QDesignerWidget::hostSelect(QAbstractWidgetHost *host)
{
    if(host != m_currentHost)
    {
        m_currentHost = host;
        if(m_currentHost!= NULL)
        {
            m_propertyView->setPropertys(m_currentHost->getPropertys(),
                                         m_formEditor->getUndoStack(m_currentHost));
            //m_formlist->setCurrentText(m_currentHost->getPropertyValue("objectName").toString());
        }
        else
        {
            //m_formlist->setCurrentIndex(-1);
            m_propertyView->setPropertys(QList<QAbstractProperty*>());
        }
        m_formEditor->selectHost(host);
        m_hostListView->selectHost(m_currentHost);
    }
}

void QDesignerWidget::formSelect(QAbstractWidgetHost *host)
{
    m_hostListView->setHost(host);
    if(host == NULL)
    {
        m_formlist->setCurrentIndex(-1);
    }
    else
    {
        m_formlist->setCurrentIndex(m_formlist->findText(
                                        host->getPropertyValue("objectName").toString()));
    }
}

void QDesignerWidget::selectLanguage()
{
    QString id = m_languageList->currentData().toString();

    QProject * project = QSoftCore::getInstance()->getProject();
    project->getLanguageManager()->setCurrentLanguage(id);
}
