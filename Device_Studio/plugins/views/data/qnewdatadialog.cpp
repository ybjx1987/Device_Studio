#include "qnewdatadialog.h"
#include "ui_qnewdatadialog.h"

#include "../../../libs/kernel/data/qdatamanager.h"
#include "../../../libs/kernel/data/qdatagroup.h"
#include "../../../libs/kernel/data/qabstractdatahost.h"
#include "../../../libs/platform/qvalidatoredit.h"
#include "../../../libs/kernel/host/qhostfactory.h"

#include <QMessageBox>

QNewDataDialog::QNewDataDialog(QDataManager * manager,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewDataDialog),
    m_dataManager(manager),
    m_nameEdit(new QValidatorEdit)
{
    ui->setupUi(this);
    setProperty("no-ManhattanStyle",true);

    QList<QDataGroup*> groups = m_dataManager->getGroups();

    foreach(QDataGroup * group,groups)
    {
        ui->comboBox->addItem(group->getGroupName(),group->getUuid());
    }

    if(groups.size()>0)
    {
        ui->comboBox->setCurrentIndex(0);
    }

    ui->gridLayout->addWidget(m_nameEdit,1,1);

    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(groupChanged()));

    QList<QAbstractHostInfo*> list = QHostFactory::getHostInfo();

    foreach(QAbstractHostInfo * info,list)
    {
        if(info->m_type == "data")
        {
            QDataHostInfo *dinfo = (QDataHostInfo*)info;
            m_typeList.append(info);
            ui->comboBox_2->addItem(dinfo->m_showName);
        }
    }

    if(m_typeList.size() > 0)
    {
        ui->comboBox_2->setCurrentIndex(0);
    }
}

QNewDataDialog::~QNewDataDialog()
{
    delete ui;
}

void QNewDataDialog::groupChanged()
{
    int index = ui->comboBox->currentIndex();

    QDataGroup * group = m_dataManager->getGroups().at(index);

    QList<QAbstractDataHost*> datas = group->getDatas();

    QStringList list;

    foreach(QAbstractDataHost * data,datas)
    {
        list.append(data->getPropertyValue("objectName").toString());
    }

    m_nameEdit->setIntermediateList(list);
}

void QNewDataDialog::on_okBtn_clicked()
{
    int index = ui->comboBox->currentIndex();

    QDataGroup * group = m_dataManager->getGroups().at(index);

    QString name = m_nameEdit->value();

    if(name == "")
    {
        QMessageBox::warning(this,tr("Error"),
                             tr("The name cann't be empty!"));
        return;
    }

    index = ui->comboBox_2->currentIndex();

    if(index < 0)
    {
        QMessageBox::warning(this,tr("Error"),
                             tr("The value type is not supplied!"));
        return;
    }

    QAbstractHostInfo * info = m_typeList.at(index);

    QAbstractDataHost * data = (QAbstractDataHost*)QHostFactory::createHost(info->m_name);

    if(data == NULL)
    {
        QMessageBox::warning(this,tr("Error"),
                             tr("Create new data failed!"));
        return;
    }

    group->addData(data);
    data->setPropertyValue("objectName",name);
    close();
}

void QNewDataDialog::on_cancelBtn_clicked()
{
    close();
}
