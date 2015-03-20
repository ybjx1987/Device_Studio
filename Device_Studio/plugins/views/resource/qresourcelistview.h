#ifndef QRESOURCELISTVIEW_H
#define QRESOURCELISTVIEW_H

#include "../../../libs/platform/qbaselistview.h"

#include <QMap>

class QResourceFile;
class QResourceManager;

class QResourceListView : public QBaseListView
{
    Q_OBJECT
public:
    QResourceListView(QWidget * parent = NULL);

    void    init(QResourceManager * manager);

    void    clear();

    void    removeFile(QList<QResourceFile *> resource);
signals:
    void    resourceSelect(QResourceFile * resource);
protected slots:
    void    resourceAdded(QResourceFile * resource);
    void    resourceDeled(QResourceFile * resource);
    void    itemSelectChanged();
protected:
    QMap<QString,QTreeWidgetItem*>          m_nameToGroup;
    QMap<QResourceFile*,QTreeWidgetItem*>   m_resourceToItem;
    QMap<QTreeWidgetItem*,QResourceFile*>   m_itemToResource;
};

#endif // QRESOURCELISTVIEW_H
