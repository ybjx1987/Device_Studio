#ifndef QALLLANGUAGEVIEW_H
#define QALLLANGUAGEVIEW_H

#include "../../../libs/platform/qbaselistview.h"

class QLanguageManager;

class QAllLanguageView : public QBaseListView
{
    Q_OBJECT
public:
    QAllLanguageView(QLanguageManager* manager,QWidget * parent = NULL);
    ~QAllLanguageView();
protected:
    void    clickEditItem(QTreeWidgetItem *item, int index);
public slots:
    void    updateItem(const QString &id,const QString &key);
    void    itemAdded(const QString &key);
    void    itemDeled(const QString &key);
protected:
    QLanguageManager    *m_languageManager;

    QMap<QString,QTreeWidgetItem*>  m_keyToItem;
    QMap<QTreeWidgetItem*,QString>  m_itemToKey;
};

#endif // QALLLANGUAGEVIEW_H
