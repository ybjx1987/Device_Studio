#include "qdeletedatadialog.h"
#include "ui_qdeletedatadialog.h"

#include "../../../libs/platform/qbaselistview.h"

#include <QHeaderView>

QDeleteDataDialog::QDeleteDataDialog(QDataManager* manager,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDeleteDataDialog),
    m_listView(new QBaseListView),
    m_dataManager(manager)
{
    ui->setupUi(this);

    ui->verticalLayout->insertWidget(0,m_listView,1);

    m_listView->setFrameStyle(QFrame::Box);
}

QDeleteDataDialog::~QDeleteDataDialog()
{
    delete ui;
}
