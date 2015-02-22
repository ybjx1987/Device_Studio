#include "qstringeditordialog.h"
#include "ui_qstringeditordialog.h"

#include "../../qsoftcore.h"
#include "../../../kernel/qproject.h"
#include "../../../kernel/language/qlanguagemanager.h"
#include "../../../kernel/language/qlanguage.h"
#include "../../qbaselistview.h"
#include "../../qlanguageid.h"
#include "../../../kernel/property/qstringproperty.h"

#include <QCompleter>
#include <QMessageBox>

QStringEditorDialog::QStringEditorDialog(QStringProperty * property,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QStringEditorDialog),
    m_listView(new QBaseListView),
    m_property(property)
{
    ui->setupUi(this);
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),
            this,SLOT(keyChanged()));
    m_languageManager = QSoftCore::getInstance()->getProject()->getLanguageManager();
    m_completer = new QCompleter(m_languageManager->getAllNames(),this);
    ui->lineEdit->setCompleter(m_completer);
    m_listView->setFrameStyle(QFrame::Box);
    m_listView->setHeaderLabels(QStringList()<<tr("Language")<<tr("Text"));
    m_listView->setColumnWidth(0,100);
    ui->verticalLayout->insertWidget(1,m_listView,1);

    foreach(QLanguage* language,m_languageManager->getLanguages())
    {
        QLanguageInfo id = QLanguageID::getLanguageInfo(language->getID());
        QTreeWidgetItem *item = new QTreeWidgetItem(m_listView);
        item->setText(0,id.m_name);
        item->setIcon(0,QIcon(id.m_icon));
        item->setToolTip(0,id.m_name);
        m_languageToItem.insert(language,item);
        m_itemToLanguage.insert(item,language);
    }

    if(m_property->getTranslation())
    {
        QLanguageItem *item = m_languageManager->getItem(m_property->getUuid());

        if(item != NULL)
        {
            ui->lineEdit->setText(item->m_name);
        }
    }
    else
    {
        ui->lineEdit->setText(m_property->getValue().toString());
    }
    m_lastSize = QSize(400,420);
    ui->checkBox->setChecked(m_property->getTranslation());
}

QStringEditorDialog::~QStringEditorDialog()
{
    delete ui;
}

void QStringEditorDialog::on_okBtn_clicked()
{
    QString name = ui->lineEdit->text();

    if(name == "")
    {
        QMessageBox::warning(this,tr("Error"),
                             tr("Keyword cann't been empty!"));
        return;
    }

    if(ui->checkBox->checkState() == Qt::Unchecked)
    {
        m_property->setValue(ui->lineEdit->text());
        m_property->setTranslation(false);
        close();
        return;
    }

    QLanguageItem * item = m_languageManager->getItemByName(name);

    if(item == NULL)
    {
        m_languageManager->addItem(name);
        item = m_languageManager->getItemByName(name);
    }

    if(item == NULL)
    {
        QMessageBox::warning(this,tr("Error"),
                             tr("Add item failed!"));
        return;
    }

    m_property->setUuid(item->m_uuid);
    m_property->setTranslation(true);
    close();
}

void QStringEditorDialog::on_cancelBtn_clicked()
{
    close();
}

void QStringEditorDialog::keyChanged()
{
    QString key = ui->lineEdit->text();

    QLanguageItem * item = m_languageManager->getItemByName(key);

    if(item != NULL)
    {
        foreach(QLanguage *language,m_languageManager->getLanguages())
        {
            QTreeWidgetItem * it = m_languageToItem.value(language);
            it->setText(1,language->getValue(item->m_uuid));
            it->setToolTip(1,language->getValue(item->m_uuid));
        }
    }
    else
    {
        foreach(QLanguage *language,m_languageManager->getLanguages())
        {
            QTreeWidgetItem * it = m_languageToItem.value(language);
            it->setText(1,key);
            it->setToolTip(1,key);
        }
    }
}

void QStringEditorDialog::on_checkBox_stateChanged(int)
{
    if(ui->checkBox->checkState()==Qt::Checked)
    {
        m_listView->setVisible(true);
        setMaximumHeight(9999);
        resize(m_lastSize);
        ui->lineEdit->setCompleter(m_completer);
    }
    else
    {
        m_listView->setVisible(false);
        m_lastSize = size();
        this->updateGeometry();
        setMaximumHeight(120);
        resize(QSize(400,90));
        ui->lineEdit->setCompleter(NULL);
    }
}
