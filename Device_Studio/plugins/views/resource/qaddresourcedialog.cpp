#include "qaddresourcedialog.h"
#include "ui_qaddresourcedialog.h"

#include "qsystemresourcedialog.h"

#include <QFileDialog>
#include <QApplication>

QAddResourceDialog::QAddResourceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QAddResourceDialog)
{
    ui->setupUi(this);
    //setProperty("no-ManhattanStyle",true);
    ui->toolButton->setPopupMode(QToolButton::MenuButtonPopup);

    QAction * ac ;

    ac = new QAction(tr("From System"),this);
    ui->toolButton->addAction(ac);
    connect(ac,SIGNAL(triggered()),this,SLOT(fromSystem()));
    ui->toolButton->setDefaultAction(ac);
    ac = new QAction(tr("From Loacl"),this);
    ui->toolButton->addAction(ac);
    connect(ac,SIGNAL(triggered()),this,SLOT(fromLocal()));
}

QAddResourceDialog::~QAddResourceDialog()
{
    delete ui;
}

void QAddResourceDialog::fromSystem()
{
    QSystemResourceDialog dlg(this);
    dlg.exec();
}

void QAddResourceDialog::fromLocal()
{
    QString str = QFileDialog::getOpenFileName(this,tr("Add Resource"),QDir::currentPath(),
                                 tr("All File(*.*)"));
    if(str != "")
    {
        ui->lineEdit->setText(str);
        m_resourceType = "local";
    }
}

void QAddResourceDialog::on_pushButton_2_clicked()
{
    close();
}

void QAddResourceDialog::on_pushButton_clicked()
{

}
