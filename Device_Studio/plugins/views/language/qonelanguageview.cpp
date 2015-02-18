#include "qonelanguageview.h"

#include "../../../libs/kernel/language/qlanguage.h"

QOneLanguageView::QOneLanguageView(QLanguage * language,QWidget* parent):
    QBaseListView(parent)
{
    setHeaderLabels(QStringList()<<tr("Default")<<language->getName());
    setColumnWidth(0,300);
}

QOneLanguageView::~QOneLanguageView()
{

}

