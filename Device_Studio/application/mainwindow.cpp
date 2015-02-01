#include "mainwindow.h"

#include "fancytabwidget.h"

#include "../libs/platform/platformlibglobal.h"
#include "../libs/platform/qplatformcore.h"
#include "../libs/platform/qsettingmanager.h"
#include "../libs/platform/manhattanstyle.h"

#include "../libs/kernel/pluginloader.h"
#include "../libs/platform/qabstractpage.h"

#include <QDesktopWidget>
#include <QApplication>

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
