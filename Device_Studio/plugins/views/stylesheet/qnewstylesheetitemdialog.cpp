#include "qnewstylesheetitemdialog.h"
#include "ui_qnewstylesheetitemdialog.h"

#include "../../../libs/kernel/stylesheet/qstylesheetmanager.h"
#include "../../../libs/kernel/stylesheet/qstylesheetgroup.h"
#include "../../../libs/kernel/stylesheet/qstylesheetitem.h"

QNewStyleSheetItemDialog::QNewStyleSheetItemDialog(QStyleSheetManager * manager,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewStyleSheetItemDialog),
    m_manager(manager)
{
    ui->setupUi(this);

    setProperty("no-ManhattanStyle",true);
    ui->groupName->addItems(manager->getGroupNames());
}

QNewStyleSheetItemDialog::~QNewStyleSheetItemDialog()
{
    delete ui;
}

void QNewStyleSheetItemDialog::on_okBtn_clicked()
{

    if(ui->groupName->currentIndex() >= 0)
    {
        QStyleSheetGroup * group = m_manager->getGroups().at(ui->groupName->currentIndex());
        QStyleSheetItem * item = new QStyleSheetItem;
        group->addItem(item);
    }
    close();
}

void QNewStyleSheetItemDialog::on_cancelBtn_clicked()
{
    close();
}
