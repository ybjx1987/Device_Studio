#ifndef QLANGUAGEITEMDELETEGATE_H
#define QLANGUAGEITEMDELETEGATE_H

#include "../../../libs/platform/qbaseitemdelegate.h"

class QLanguageItemDeletegate : public QBaseItemDelegate
{
    Q_OBJECT
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void    setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
signals:
    void    editValue(const QString &value,const QModelIndex &index)const;
};

#endif // QLANGUAGEITEMDELETEGATE_H
