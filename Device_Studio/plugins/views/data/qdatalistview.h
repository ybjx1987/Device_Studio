#ifndef QDATALISTVIEW_H
#define QDATALISTVIEW_H

#include "../../../libs/platform/qbaselistview.h"
#include "../../../libs/platform/qbaseitemdelegate.h"

#include <QMap>

class QAbstractDataHost;
class QDataGroup;
class QDataListView;
class QDataManager;
class QAbstractProperty;

class QDataItemDelegate : public QBaseItemDelegate
{
public:
    QDataItemDelegate(QDataListView * listView):m_listView(listView){}

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void    setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
protected:
    QDataListView   *m_listView;
};

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
    void    clickEditItem(QTreeWidgetItem *item, int index);

    void    connectDataHost(QAbstractDataHost * data);
    void    disconnectDataHost(QAbstractDataHost * data);

    void    connectGroup(QDataGroup * group);
    void    disconnectGroup(QDataGroup * group);
protected slots:
    void    groupAdded(QDataGroup * group,int index);
    void    groupDeled(QDataGroup * group);

    void    dataAdded(QAbstractDataHost * data,int index);
    void    dataDeled(QAbstractDataHost * data);

    void    dataSelect();

    void    dataPropertyChanged();
    void    groupNameChanged();

    void    propertyValueEdit(QAbstractProperty* property,const QVariant &value);

    friend class QDataItemDelegate;
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
