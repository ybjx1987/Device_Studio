#include "mainwindow.h"

#include "fancytabwidget.h"
#include "qnewprojectdialog.h"

#include "../libs/platform/platformlibglobal.h"
#include "../libs/platform/qplatformcore.h"
#include "../libs/platform/qsettingmanager.h"
#include "../libs/platform/manhattanstyle.h"

#include "../libs/kernel/pluginloader.h"
#include "../libs/platform/qabstractpage.h"
#include "../libs/platform/qsoftactionmap.h"
#include "../libs/platform/qsoftcore.h"
#include "../libs/kernel/qproject.h"
#include "../libs/kernel/host/qhostfactory.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>

bool pageCheck(QAbstractPlugin *plugin1,QAbstractPlugin * plugin2)
{
    return ((QAbstractPage*)plugin1)->getPageIndex()<((QAbstractPage*)plugin2)->getPageIndex();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_fancyTab(new FancyTabWidget(this))
{
    qApp->setStyle(new ManhattanStyle(qApp->style()->objectName()));
    setCentralWidget(m_fancyTab);

    QMap<QString,QAbstractPlugin*>  pages = PluginLoader::getPluginByType("Plugin.Page");

    QList<QAbstractPlugin*> list = pages.values();

    qSort(list.begin(),list.end(),pageCheck);

    foreach(QAbstractPlugin * plugin,list)
    {
        QAbstractPage * page = (QAbstractPage*)plugin;
        m_fancyTab->insertTab(list.indexOf(plugin),page->getWidget(),
                              page->getPageIcon(),page->getPageText());
    }

    if(list.size()>0)
    {
        m_fancyTab->setCurrentIndex(0);
    }

    connect(QSoftCore::getInstance()->getProject(),SIGNAL(projectStatusChanged(enProjectStatus)),
            this,SLOT(projectStatusChanged()));

    QAction* ac;

    ac = QSoftActionMap::getAction("project.open");
    if(ac != NULL)
    {
        connect(ac,SIGNAL(triggered()),this,SLOT(openProject()));
    }

    ac = QSoftActionMap::getAction("project.new");
    if(ac != NULL)
    {
        connect(ac,SIGNAL(triggered()),this,SLOT(newProject()));
    }

    projectStatusChanged();

    QAbstractWidgetHost * host = (QAbstractWidgetHost*)QHostFactory::createHost("form");
    if(host == NULL)
    {
        qDebug("Host is NULL");
    }
    else
    {
        QSoftCore::getInstance()->getProject()->addForm(host);
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::show()
{
    QSettingManager *manager = QPlatformCore::getInstance()->getSettingManager();
    QVariant value = manager->getValue("window.geometry");
    if(value.isValid())
    {
        QByteArray array = value.toByteArray();
        restoreGeometry(value.toByteArray());
    }
    else
    {
        QDesktopWidget *dw = qApp->desktop();
        setGeometry(dw->width()/10,
                    dw->height()/10,
                    dw->width()*0.8,
                    dw->height()*0.8);
        saveSetting();
    }
    QMainWindow::show();
}

void MainWindow::saveSetting()
{
    QSettingManager *manager = QPlatformCore::getInstance()->getSettingManager();
    manager->setValue("window.geometry",saveGeometry());
    manager->save();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    saveSetting();
    QMainWindow::closeEvent(e);
}

void MainWindow::openProject()
{
    QProject * project = QSoftCore::getInstance()->getProject();
    if(project->getProjectStatus() == PS_OPENED)
    {
        if(QMessageBox::warning(this,tr("Warning"),tr("This action will close the current project, would you continue?")
                                ,QMessageBox::Yes | QMessageBox::No)
                != QMessageBox::Yes)
        {
            return;
        }
    }
    else if(project->getProjectStatus() == PS_OPENING)
    {
        return;
    }

    QString path = QFileDialog::getOpenFileName(this,tr("Open Project"),
                                 QDir::currentPath(),tr("Project File (*.pfl)"));
    if(path != "")
    {
        qDebug(path.toLocal8Bit());
    }
}

void MainWindow::projectStatusChanged()
{
    enProjectStatus status = QSoftCore::getInstance()->getProject()->getProjectStatus();
    QAction *ac;

    ac = QSoftActionMap::getAction("project.new");
    if(ac != NULL)
    {
        ac->setEnabled(status != PS_OPENING);
    }

    ac = QSoftActionMap::getAction("project.close");
    if(ac != NULL)
    {
        ac->setEnabled(status == PS_OPENED);
    }

    ac = QSoftActionMap::getAction("project.save");
    if(ac != NULL)
    {
        ac->setEnabled(status == PS_OPENED);
    }

    ac = QSoftActionMap::getAction("project.new");
    if(ac != NULL)
    {
        ac->setEnabled(status != PS_OPENING);
    }
}

void MainWindow::newProject()
{
    QNewProjectDialog dlg(this);

    dlg.exec();

    QString name = dlg.getName();
    QString path = dlg.getPath();

    if(name != "" && path != "")
    {
        QSoftCore::getInstance()->newProject(path,name);
    }
}
