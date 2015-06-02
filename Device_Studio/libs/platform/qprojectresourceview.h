#ifndef QPROJECTRESOURCEVIEW_H
#define QPROJECTRESOURCEVIEW_H

#include "qbaselistview.h"

#include <QMap>

class QResourceFile;

class QProjectResourceView : public QBaseListView
{
    Q_OBJECT
public:
    explicit QProjectResourceView(QWidget *parent = 0);
    ~QProjectResourceView();

signals:
    void fileSelect(QResourceFile * file);
protected slots:
    void doubleClickItem(QTreeWidgetItem * item);
protected:
    QMap<QTreeWidgetItem*,QResourceFile*>   m_itemToFile;
    QMap<QString,QTreeWidgetItem*>          m_nameToGroup;
};

#endif // QPROJECTRESOURCEVIEW_H
