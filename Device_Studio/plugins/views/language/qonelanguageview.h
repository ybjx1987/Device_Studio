#ifndef QONELANGUAGEVIEW_H
#define QONELANGUAGEVIEW_H

#include "../../../libs/platform/qbaselistview.h"

class QLanguage;

class QOneLanguageView : public QBaseListView
{
    Q_OBJECT
public:
    QOneLanguageView(QLanguage * language,QWidget* parent =NULL);
    ~QOneLanguageView();
protected:
    void  clickEditItem(QTreeWidgetItem *item, int index);
protected slots:
    void    itemAdded(const QString &key);
    void    itemDeled(const QString &key);
protected:
    QLanguage   *m_language;

    QMap<QString,QTreeWidgetItem*>  m_keyToItem;
    QMap<QTreeWidgetItem*,QString>  m_itemToKey;
};

#endif // QONELANGUAGEVIEW_H
