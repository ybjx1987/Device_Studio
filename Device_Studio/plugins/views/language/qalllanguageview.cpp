#include "qalllanguageview.h"

#include "qlanguageitemdeletegate.h"

#include "../../../libs/kernel/language/qlanguagemanager.h"
#include "../../../libs/kernel/language/qlanguage.h"
#include "../../../libs/platform/qlanguageid.h"

QAllLanguageView::QAllLanguageView(QLanguageManager* manager,QWidget* parent):
    QBaseListView(parent),
    m_languageManager(manager)
{
    QStringList list;
    list<<tr("Default");

    foreach(QLanguage * language,m_languageManager->getLanguages())
    {
        QLanguageInfo info = QLanguageID::getLanguageInfo(language->getID());
        list.append(info.m_name);
    }

    setHeaderLabels(list);

    for(int i= 0;i<list.size();i++)
    {
        setColumnWidth(i,200);
    }

    QStringList l = m_languageManager->getAllKeyword();
    foreach(QString str,l)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(this);
        item->setText(0,str);
        item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        for(int i = 0;i<list.size();i++)
        {
            item->setText(i+1,m_languageManager->getLanguages().at(i)->getValue(str));
        }
        m_itemToKey.insert(item,str);
        m_keyToItem.insert(str,item);
    }

    connect(m_languageManager,SIGNAL(itemDeled(QString)),
            this,SLOT(itemDeled(QString)));
    connect(m_languageManager,SIGNAL(itemAdded(QString)),
            this,SLOT(itemAdded(QString)));
    connect(m_languageManager,SIGNAL(updateItem(QString,QString)),
            this,SLOT(updateItem(QString,QString)));

    m_itemDeletegate = new QLanguageItemDeletegate;
    setItemDelegate(m_itemDeletegate);

    connect(m_itemDeletegate,SIGNAL(editValue(QString,QModelIndex)),
            this,SLOT(updateItem(QString,QModelIndex)));

    foreach(QLanguage *language,m_languageManager->getLanguages())
    {
        connect(language,SIGNAL(itemUpdated(QString)),
                this,SLOT(updateItem(QString)));
    }
}

QAllLanguageView::~QAllLanguageView()
{

}

void QAllLanguageView::itemAdded(const QString &key)
{
    QTreeWidgetItem * item = m_keyToItem.value(key);
    if(item != NULL)
    {
        return;
    }

    item = new QTreeWidgetItem(this);
    item->setText(0,key);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    m_keyToItem.insert(key,item);
    m_itemToKey.insert(item,key);
}

void QAllLanguageView::itemDeled(const QString &key)
{
    QTreeWidgetItem * item = m_keyToItem.value(key);
    if(item != NULL)
    {
        m_keyToItem.remove(key);
        m_itemToKey.remove(item);
        delete item;
    }
}

void QAllLanguageView::updateItem(const QString &id, const QString &key)
{
    QLanguage *language = m_languageManager->getLanguage(id);

    if(language != NULL)
    {
        QTreeWidgetItem * item = m_keyToItem.value(key);
        if(item != NULL)
        {
            item->setText(m_languageManager->getLanguages().indexOf(language)+1,
                      language->getValue(key));
        }
    }
}

void QAllLanguageView::clickEditItem(QTreeWidgetItem *item,int index)
{
    if(index != 0)
    {
        editItem(item,index);
    }
}

void QAllLanguageView::updateItem(const QString &value, const QModelIndex &index)
{
    QTreeWidgetItem * item = itemFromIndex(index);

    QLanguage * language = m_languageManager->getLanguages().at(index.column()-1);
    if(language != NULL)
    {
        language->setValue(m_itemToKey.value(item),value);
    }
    item->setText(index.column(),value);
}

void QAllLanguageView::updateItem(const QString &key)
{
    QLanguage * language = (QLanguage*)sender();
    QTreeWidgetItem * item = m_keyToItem.value(key);

    if(item != NULL && language != NULL)
    {
        item->setText(m_languageManager->getLanguages().indexOf(language)+1,
                      language->getValue(key));
    }
}
