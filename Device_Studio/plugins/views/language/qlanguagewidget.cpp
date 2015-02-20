#include "qlanguagewidget.h"

#include "qlanguagelist.h"
#include "qonelanguageview.h"
#include "qnewlanguagedialog.h"
#include "qdellanguagedialog.h"
#include "qnewitemdialog.h"
#include "qdeleteitemdialog.h"

#include "../../../libs/platform/styledbar.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/platform/minisplitter.h"
#include "../../../libs/kernel/language/qlanguagemanager.h"
#include "../../../libs/kernel/language/qlanguage.h"
#include "../../../libs/platform/qsoftactionmap.h"
#include "../../../libs/platform/qactiontoolbar.h"

#include <QVBoxLayout>
#include <QMessageBox>

QLanguageWidget::QLanguageWidget(QWidget* parent):
    QAbstractPageWidget(parent),
    m_languageListBar(new StyledBar),
    m_languageList(new QLanguageList),
    m_languageViewBar(new StyledBar),
    m_languageView(new QStackedWidget),
    m_selectUuid("")
{
    MiniSplitter *sp = new MiniSplitter;
    QWidget * wid;
    QVBoxLayout *v ;
    wid= new QWidget;
    v= new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(m_languageListBar);
    v->addWidget(m_languageList);
    wid->setLayout(v);
    sp->addWidget(wid);

    wid= new QWidget;
    v= new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(m_languageViewBar);
    v->addWidget(m_languageView);
    wid->setLayout(v);
    sp->addWidget(wid);

    v= new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(sp);
    setLayout(v);

    sp->setStretchFactor(0,0);
    sp->setStretchFactor(1,1);

    QProject * project = QSoftCore::getInstance()->getProject();
    connect(project,SIGNAL(projectClosed()),
            this,SLOT(projectClosed()));
    connect(project,SIGNAL(projectOpened()),
            this,SLOT(projectOpened()));

    initAction();

    QActionToolBar *toolBar = new QActionToolBar;

    v = new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(toolBar);

    m_languageListBar->setLayout(v);

    QList<QAction*> list;

    list.append(QSoftActionMap::getAction("language.add"));
    list.append(QSoftActionMap::getAction("language.del"));
    QAction *ac = new QAction(this);
    ac->setSeparator(true);
    list.append(ac);
    toolBar->addButtonActions(list);

    list.clear();
    toolBar = new QActionToolBar;
    v = new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(toolBar);
    m_languageViewBar->setLayout(v);
    list.append(QSoftActionMap::getAction("language.item.add"));
    list.append(QSoftActionMap::getAction("language.item.del"));
    ac = new QAction(this);
    ac->setSeparator(true);
    list.append(ac);
    toolBar->addButtonActions(list);

    connect(m_languageList,SIGNAL(select(QString)),this,SLOT(languageSelect(QString)));

    updateAction();

    connect(QSoftActionMap::getAction("language.add"),
            SIGNAL(triggered()),this,SLOT(addLanguage()));

    connect(QSoftActionMap::getAction("language.del"),
            SIGNAL(triggered()),this,SLOT(delLanguage()));

    connect(QSoftActionMap::getAction("language.item.add"),
            SIGNAL(triggered()),this,SLOT(addItem()));
    connect(QSoftActionMap::getAction("language.item.del"),
            SIGNAL(triggered()),this,SLOT(delItem()));
}

void QLanguageWidget::projectClosed()
{
    clear();

}

void QLanguageWidget::clear()
{
    m_languageList->clear();

    QMapIterator<QString,QWidget*>  it(m_uuidToQWidget);

    while(it.hasNext())
    {
        it.next();
        m_languageView->removeWidget(it.value());
    }

    qDeleteAll(m_uuidToQWidget.values());
    m_uuidToQWidget.clear();

    m_selectUuid = "";
    updateAction();
}

void QLanguageWidget::projectOpened()
{
    clear();

    QLanguageManager *manager = QSoftCore::getInstance()->getProject()->getLanguageManager();

    foreach(QLanguage* language,manager->getLanguages())
    {
        insertLanguage(language);
    }

    updateAction();

    connect(manager,SIGNAL(languageAdd(QString)),this,SLOT(languageAdded(QString)));
    connect(manager,SIGNAL(languageDel(QLanguage*)),
            this,SLOT(languageDeled(QLanguage*)));
}

void QLanguageWidget::insertLanguage(QLanguage *language,int index)
{
    if(index <0 || index>m_languageView->count())
    {
        index = m_languageView->count();
    }

    m_languageList->insertLanguage(language);

    QOneLanguageView *view = new QOneLanguageView(language);
    m_languageView->insertWidget(index,view);

    m_uuidToQWidget.insert(language->getID(),view);
}

void QLanguageWidget::initAction()
{
    QAction *ac;

    ac = new QAction(QIcon(":/inner/images/add.png"),tr("Add"),this);
    QSoftActionMap::insertAction("language.item.add",ac);

    ac = new QAction(QIcon(":/inner/images/add.png"),tr("Add"),this);
    QSoftActionMap::insertAction("language.add",ac);

    ac = new QAction(QIcon(":/inner/images/del.png"),tr("Del"),this);
    QSoftActionMap::insertAction("language.item.del",ac);

    ac = new QAction(QIcon(":/inner/images/del.png"),tr("Del"),this);
    QSoftActionMap::insertAction("language.del",ac);
}

void QLanguageWidget::languageSelect(const QString &uuid)
{
    QWidget * wid = m_uuidToQWidget.value(uuid);

    if(wid != NULL)
    {
        m_languageView->setCurrentWidget(wid);
    }
    m_selectUuid = uuid;
    updateAction();
}

void QLanguageWidget::updateAction()
{
    QAction *ac;
    if(m_selectUuid == "")
    {
        ac = QSoftActionMap::getAction("language.add");
        ac->setEnabled(true);
        ac = QSoftActionMap::getAction("language.del");
        ac->setEnabled(false);
        ac = QSoftActionMap::getAction("language.item.del");
        ac->setEnabled(false);
        ac = QSoftActionMap::getAction("language.item.add");
        ac->setEnabled(false);

    }
    else
    {
        ac = QSoftActionMap::getAction("language.add");
        ac->setEnabled(true);
        ac = QSoftActionMap::getAction("language.del");
        ac->setEnabled(true);
        ac = QSoftActionMap::getAction("language.item.del");
        ac->setEnabled(true);
        ac = QSoftActionMap::getAction("language.item.add");
        ac->setEnabled(true);
    }

}

void QLanguageWidget::addLanguage()
{
    QNewLanguageDialog dialog;

    dialog.exec();

    QString  id = dialog.getLanguageID();

    if(id != "")
    {
        QLanguageManager * manager = QSoftCore::getInstance()->getProject()->getLanguageManager();
        QString str = manager->addLanguage(id);
        if(str != "")
        {
            QMessageBox::warning(this,tr("Error"),str);
        }
    }
}

void QLanguageWidget::languageAdded(const QString &id)
{
    QLanguageManager *manager = QSoftCore::getInstance()->getProject()->getLanguageManager();

    QLanguage *language = manager->getLanguage(id);

    insertLanguage(language,-1);
}

void QLanguageWidget::languageDeled(QLanguage * language)
{
    m_languageList->removeLanguage(language);
    QWidget* wid = m_uuidToQWidget.value(language->getID());
    delete wid;
    m_uuidToQWidget.remove(language->getID());
}

void QLanguageWidget::delLanguage()
{
    QDelLanguageDialog dlg(this);

    dlg.exec();
}

void QLanguageWidget::addItem()
{
    QLanguageManager *manager = QSoftCore::getInstance()->getProject()->getLanguageManager();
    QStringList list;
    QLanguage* language = manager->getLanguage(m_selectUuid);
    list = language->getKeys();
    QNewItemDialog dlg(list,this);

    dlg.exec();

    QString key = dlg.getKey();

    if(key != "")
    {
        language->addItem(key,dlg.getValue());
    }
}

void QLanguageWidget::delItem()
{
    QLanguageManager *manager = QSoftCore::getInstance()->getProject()->getLanguageManager();
    QStringList list;
    QLanguage *language = manager->getLanguage(m_selectUuid);
    list = language->getKeys();
    QDeleteItemDialog dlg(list,this);
    dlg.exec();

    list = dlg.getSelection();

    foreach(QString str,list)
    {
        language->delItem(str);
    }
}
