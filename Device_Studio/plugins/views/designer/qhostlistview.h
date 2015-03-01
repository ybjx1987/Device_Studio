#ifndef QHOSTLISTVIEW_H
#define QHOSTLISTVIEW_H

#include "../../../libs/platform/qbaselistview.h"

#include <QMap>

class QAbstractHost;
class QAbstractWidgetHost;

class QHostListView : public QBaseListView
{
    Q_OBJECT
public:
    QHostListView(QWidget* parent = NULL);

    void    setHost(QAbstractHost* host);
    void    selectHost(QAbstractHost * host);

    void    clear();
protected:
    void    insertHost(QAbstractHost * host);
protected slots:
    void    selectChanged();
    void    addHost(QAbstractHost * host);
    void    removeHost(QAbstractHost * host);

    void    hostNameChanged();
signals:
    void    hostSelectChanged(QAbstractWidgetHost * host);
protected:
    QMap<QAbstractHost*,QTreeWidgetItem*>   m_hostToItem;
    QMap<QTreeWidgetItem*,QAbstractHost*>   m_itemToHost;
    QAbstractHost                           *m_selectHost;
    QAbstractHost                           *m_rootHost;
};

#endif // QHOSTLISTVIEW_H
