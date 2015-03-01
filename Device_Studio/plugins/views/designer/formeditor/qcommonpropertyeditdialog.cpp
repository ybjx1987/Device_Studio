#include "qcommonpropertyeditdialog.h"
#include "ui_qcommonpropertyeditdialog.h"

#include "../../../libs/platform/propertylist/qpropertyeditorpane.h"
#include "../../../libs/kernel/property/qabstractproperty.h"

QCommonPropertyEditDialog::QCommonPropertyEditDialog(QAbstractProperty *proeprty,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCommonPropertyEditDialog),
    m_property(proeprty)
{
    ui->setupUi(this);

    QPropertyEditorPane *panel = new QPropertyEditorPane(m_property,this);
    panel->setShowResetButton(false);
    connect(panel,SIGNAL(propertyValueEdit(QAbstractProperty*,QVariant)),
            this,SLOT(propertyValueEdit(QAbstractProperty*,QVariant)));
    m_value = m_property->getValue();
    ui->verticalLayout->insertWidget(0,panel,1);

    QString title = tr("Edit [")+m_property->getShowName()+"] value";
    setWindowTitle(title);
}

QCommonPropertyEditDialog::~QCommonPropertyEditDialog()
{
    delete ui;
}

void QCommonPropertyEditDialog::on_okBtn_clicked()
{
    close();
}

void QCommonPropertyEditDialog::on_cancelBtn_clicked()
{
    m_value = QVariant();
    close();
}

void QCommonPropertyEditDialog::propertyValueEdit(QAbstractProperty *property, const QVariant &value)
{
    m_value = value;
}

QVariant QCommonPropertyEditDialog::getValue()
{
    return m_value;
}
