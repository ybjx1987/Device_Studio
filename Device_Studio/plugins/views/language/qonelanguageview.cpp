#include "qonelanguageview.h"

#include "../../../libs/kernel/language/qlanguage.h"
#include "../../../libs/platform/qlanguageid.h"

QOneLanguageView::QOneLanguageView(QLanguage * language,QWidget* parent):
    QBaseListView(parent)
{
    QLanguageInfo info = QLanguageID::getLanguageInfo(language->getID());
    setHeaderLabels(QStringList()<<tr("Default")<<info.m_name);
    setColumnWidth(0,300);
}

QOneLanguageView::~QOneLanguageView()
{

}

