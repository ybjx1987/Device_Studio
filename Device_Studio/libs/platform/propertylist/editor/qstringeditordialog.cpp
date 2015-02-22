#include "qstringeditordialog.h"
#include "ui_qstringeditordialog.h"

#include "../../qsoftcore.h"
#include "../../../kernel/qproject.h"
#include "../../../kernel/language/qlanguagemanager.h"
#include "../../../kernel/language/qlanguage.h"
#include "../../qbaselistview.h"
#include "../../qlanguageid.h"

#include <QCompleter>
#include <QMessageBox>

QStringEditorDialog::QStringEditorDialog(const QString &uuid,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QStringEditorDialog),
    m_listView(new QBaseListView),
    m_ret(0)
{
    ui->setupUi(this);
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),
            this,SLOT(keyChanged()));
    m_languageManager = QSoftCore::getInstance()->getProject()->getLanguageManager();
    QCompleter * p = new QCompleter(m_languageManager->getAllNames());
    ui->lineEdit->setCompleter(p);
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

    QLanguageItem *item = m_languageManager->getItem(uuid);

    if(item != NULL)
    {
        m_uuid = uuid;
        ui->lineEdit->setText(item->m_name);
    }
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

    m_uuid = item->m_uuid;

    close();
    m_ret = 1;
}

void QStringEditorDialog::on_cancelBtn_clicked()
{
    close();
    m_ret = 0;
}

QString QStringEditorDialog::getUuid()
{
    return m_uuid;
}

int QStringEditorDialog::getRet()
{
    return m_ret;
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
