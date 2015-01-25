#include "mainwindow.h"

#include "../libs/platform/platformlibglobal.h"
#include "../libs/platform/qplatformcore.h"
#include "../libs/platform/qsettingmanager.h"

#include <QDesktopWidget>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
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
