#include "qlanguagelist.h"

#include "../../../libs/kernel/language/qlanguage.h"
#include "../../../libs/platform/qbaseitemdelegate.h"
#include "../../../libs/platform/qlanguageid.h"

#include <QIcon>
#include <QHeaderView>

QLanguageList::QLanguageList(QWidget* parent):
    QBaseListView(parent),
    m_rootItem(NULL)
{
    header()->hide();
    setRootIsDecorated(true);
    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(itemSelected()));
}

QLanguageList::~QLanguageList()
{

}

void QLanguageList::insertLanguage(QLanguage *language, int index)
{
    if(m_rootItem == NULL)
    {
        m_rootItem = new QTreeWidgetItem(this);
        m_rootItem->setText(0,tr("All Language"));
        m_rootItem->setToolTip(0,tr("All Language"));
        m_rootItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m_rootItem->setData(0,DarkRole,true);
        m_rootItem->setExpanded(true);
        m_rootItem->setSelected(true);
        select("rootItem");
    }
    if(index <0 && index > m_languages.size())
    {
        index = m_languages.size();
    }
    QLanguageInfo info = QLanguageID::getLanguageInfo(language->getID());
    QTreeWidgetItem * item = new QTreeWidgetItem(m_rootItem);
    item->setText(0,info.m_name);
    item->setToolTip(0,info.m_name);
    item->setIcon(0,QIcon(info.m_icon));
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_languages.insert(index,language);
    m_itemToLanguage.insert(item,language);
    m_languageToItem.insert(language,item);
}

void QLanguageList::clear()
{
    m_languages.clear();
    m_languageToItem.clear();
    m_itemToLanguage.clear();
    QBaseListView::clear();
}

void QLanguageList::itemSelected()
{
    QMapIterator<QLanguage*,QTreeWidgetItem*>    it(m_languageToItem);

    if(m_rootItem->isSelected())
    {
        emit select("rootItem");
        return;
    }

    while(it.hasNext())
    {
        it.next();
        if(it.value()->isSelected())
        {
            emit select(it.key()->getID());
            return;
        }
    }
}

void QLanguageList::removeLanguage(QLanguage *language)
{
    if(!m_languages.contains(language))
    {
        return;
    }
    QTreeWidgetItem * item = m_languageToItem.value(language);

    m_languages.removeAll(language);
    m_itemToLanguage.remove(item);
    m_languageToItem.remove(language);
    delete item;
    if(m_languages.size() == 0)
    {
        delete m_rootItem;
        m_rootItem = NULL;
    }
}
