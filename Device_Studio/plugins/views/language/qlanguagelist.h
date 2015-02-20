#ifndef QLANGUAGELIST_H
#define QLANGUAGELIST_H

#include "../../../libs/platform/qbaselistview.h"

#include <QMap>

class QLanguage;

class QLanguageList : public QBaseListView
{
    Q_OBJECT
public:
    QLanguageList(QWidget* parent=NULL);
    ~QLanguageList();

    void    clear();
    void    insertLanguage(QLanguage * language,int index=-1);
    void    removeLanguage(QLanguage* language);
protected slots:
    void    itemSelected();
signals:
    void    select(const QString &uuid);
protected:
    QMap<QLanguage*,QTreeWidgetItem*>   m_languageToItem;
    QMap<QTreeWidgetItem*,QLanguage*>   m_itemToLanguage;

    QList<QLanguage*>                   m_languages;
    QTreeWidgetItem*                    m_rootItem;
};

#endif // QLANGUAGELIST_H
