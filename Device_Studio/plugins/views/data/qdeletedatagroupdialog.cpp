#include "qdeletedatagroupdialog.h"
#include "ui_qdeletedatagroupdialog.h"

#include "../../../libs/platform/qbaselistview.h"

#include "../../../libs/kernel/data/qdatamanager.h"
#include "../../../libs/kernel/data/qdatagroup.h"

#include <QHeaderView>

QDeleteDataGroupDialog::QDeleteDataGroupDialog(QDataManager * manager,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDeleteDataGroupDialog),
    m_listView(new QBaseListView),
    m_dataManager(manager)
{
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0,m_listView,1);

    m_listView->setFrameStyle(QFrame::Box);
    m_listView->header()->hide();

    foreach(QDataGroup * group,m_dataManager->getGroups())
    {
        QTreeWidgetItem * item = new QTreeWidgetItem(m_listView);
        item->setText(0,group->getGroupName());
        item->setToolTip(0,group->getGroupName());
        item->setCheckState(0,Qt::Unchecked);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        m_itemToGroup.insert(item,group);
    }

    connect(m_listView,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(groupClicked(QTreeWidgetItem*)));
}

QDeleteDataGroupDialog::~QDeleteDataGroupDialog()
{
    delete ui;
}

void QDeleteDataGroupDialog::groupClicked(QTreeWidgetItem *item)
{
    if(item->checkState(0) == Qt::Checked)
    {
        item->setCheckState(0,Qt::Unchecked);
    }
    else
    {
        item->setCheckState(0,Qt::Checked);
    }
}

void QDeleteDataGroupDialog::on_okBtn_clicked()
{
    QMapIterator<QTreeWidgetItem*,QDataGroup*> it(m_itemToGroup);

    while(it.hasNext())
    {
        it.next();
        if(it.key()->checkState(0) == Qt::Checked)
        {
            m_dataManager->delGroup(it.value());
        }
    }
    close();
}

void QDeleteDataGroupDialog::on_cancelBtn_clicked()
{
    close();
}
