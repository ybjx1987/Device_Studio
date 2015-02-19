#include "qonelanguageview.h"

#include "../../../libs/kernel/language/qlanguage.h"
#include "../../../libs/platform/qlanguageid.h"

QOneLanguageView::QOneLanguageView(QLanguage * language,QWidget* parent):
    QBaseListView(parent),
    m_language(language)
{
    QLanguageInfo info = QLanguageID::getLanguageInfo(language->getID());
    setHeaderLabels(QStringList()<<tr("Default")<<info.m_name);
    setColumnWidth(0,300);

    connect(language,SIGNAL(itemAdded(QString)),this,SLOT(itemAdded(QString)));
    connect(language,SIGNAL(itemDeled(QString)),this,SLOT(itemDeled(QString)));

    QStringList list = m_language->getKeys();

    foreach(QString str,list)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(this);
        item->setText(0,str);
        item->setText(1,m_language->getValue(str));
        m_keyToItem.insert(str,item);
        m_itemToKey.insert(item,str);
    }
}

QOneLanguageView::~QOneLanguageView()
{

}

void QOneLanguageView::itemAdded(const QString &key)
{
    if(m_keyToItem.keys().contains(key))
    {
        return;
    }

    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setText(0,key);
    item->setText(1,m_language->getValue(key));
    m_keyToItem.insert(key,item);
    m_itemToKey.insert(item,key);
}

void QOneLanguageView::itemDeled(const QString &key)
{
    QTreeWidgetItem *item = m_keyToItem.value(key);

    m_keyToItem.remove(key);
    m_itemToKey.remove(item);
    delete item;
}
