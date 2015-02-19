#include "qalllanguageview.h"

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
}

QAllLanguageView::~QAllLanguageView()
{

}

