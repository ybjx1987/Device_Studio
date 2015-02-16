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
#include "../libs/kernel/host/qprojecthost.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QVariant>

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

    connect(QSoftCore::getInstance()->getProject(),SIGNAL(modifiedChanged()),
            this,SLOT(projectModifiedChanged()));


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

    ac = QSoftActionMap::getAction("project.save");
    if(ac != NULL)
    {
        connect(ac,SIGNAL(triggered()),this,SLOT(saveProject()));
    }

    ac = QSoftActionMap::getAction("project.close");
    if(ac != NULL)
    {
        connect(ac,SIGNAL(triggered()),this,SLOT(closeProject()));
    }

    projectStatusChanged();

    QProject * project = QSoftCore::getInstance()->getProject();
    project->open("/Users/yubing/Documents/Qt/xyz/project.pfl");
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
    project->close();
    QString path = QFileDialog::getOpenFileName(this,tr("Open Project"),
                                 QDir::currentPath(),tr("Project File (*.pfl)"));
    if(path != "")
    {
        project->open(path);
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

    updateTitle();
}

void MainWindow::newProject()
{
    QNewProjectDialog dlg(this);

    dlg.exec();

    QString name = dlg.getName();
    QString path = dlg.getPath();

    if(name != "" && path != "")
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
        project->close();
        QSoftCore::getInstance()->newProject(path,name);
    }
}

void MainWindow::saveProject()
{
    QSoftCore::getInstance()->saveProject();
}

void MainWindow::closeProject()
{
    QSoftCore::getInstance()->getProject()->close();
}

void MainWindow::projectModifiedChanged()
{
    updateTitle();
}

void MainWindow::updateTitle()
{
    QProject *project = QSoftCore::getInstance()->getProject();
    enProjectModified modified = project->getProjectModified();
    enProjectStatus   status = project->getProjectStatus();

    QString str;
    str = "Device Studio";
    if(status == PS_OPENED)
    {
        str += " [";
        str += project->getProjectHost()->getPropertyValue("objectName").toString();
        if(modified == PM_MODIFIED)
        {
            str +="*";
        }
        str += "]";
    }

    setWindowTitle(str);
}
