#ifndef QDATALISTVIEW_H
#define QDATALISTVIEW_H

#include "../../../libs/platform/qbaselistview.h"

#include <QMap>

class QAbstractDataHost;
class QDataGroup;
class QDataManager;

class QDataListView : public QBaseListView
{
    Q_OBJECT
public:
    QDataListView(QWidget * parent = NULL);

    void    setDataManager(QDataManager * manager);
    void    clear();
protected:
    void    addGroup(QDataGroup* group,int index=-1);
    void    addData(QDataGroup* group,QAbstractDataHost* data,int index = -1);
protected slots:
    void    groupAdded(QDataGroup * group,int index);
    void    groupDeled(QDataGroup * group);

    void    dataAdded(QAbstractDataHost * data,int index);
    void    dataDeled(QAbstractDataHost * data);

    void    dataSelect();
signals:
    void    updateAction();
    void    dataSelected(QAbstractDataHost* data);
protected:
    QMap<QAbstractDataHost*,QTreeWidgetItem*>   m_dataToItem;
    QMap<QTreeWidgetItem*,QAbstractDataHost*>   m_itemToData;

    QMap<QDataGroup*,QTreeWidgetItem*>          m_groupToItem;
    QMap<QTreeWidgetItem*,QDataGroup*>          m_itemToGroup;

    QDataManager        *m_dataManager;
};

#endif // QDATALISTVIEW_H
