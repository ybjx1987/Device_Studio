#include "qlanguageitemdeletegate.h"

#include "../../../libs/platform/qbuttonlineedit.h"

QWidget* QLanguageItemDeletegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QButtonLineEdit* wid = NULL;

    if(index.column() != 0)
    {
        wid = new QButtonLineEdit(parent);
    }
    return wid;
}
