#include "qhostlistview.h"

#include "../../../libs/kernel/host/qwidgethost.h"
#include "../../../libs/kernel/host/qhostfactory.h"
#include "../../../libs/platform/qbaseitemdelegate.h"
#include "../../../libs/kernel/host/qabstractwidgethost.h"

#include <QVariant>
#include <QHeaderView>


QHostListView::QHostListView(QWidget* parent ):
    QBaseListView(parent),
    m_selectHost(NULL),
    m_rootHost(NULL)
{
    setRootIsDecorated(true);
    header()->hide();
    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(selectChanged()));
}

void QHostListView::setHost(QAbstractHost *host)
{
    clear();
    m_rootHost = host;
    if(host != NULL)
    {
        insertHost(host);
    }
}

void QHostListView::insertHost(QAbstractHost *host)
{
    QAbstractHost * parent = host->getParent();

    QTreeWidgetItem *item;

    if(parent == NULL)
    {
        item = new QTreeWidgetItem(this);
    }
    else
    {
        QTreeWidgetItem *parentItem;
        parentItem = m_hostToItem.value(parent);
        item = new QTreeWidgetItem;
        parentItem->insertChild(parent->getChildrenHost().indexOf(host),item);
    }
    if(m_rootHost == host)
    {
        item->setIcon(0,QIcon(":/inner/images/widgets/frame.png"));
        item->setData(0,DarkRole,true);
    }
    else
    {
        QWidgetHostInfo *info = (QWidgetHostInfo*)QHostFactory::getHostInfo(host->property("hostName").toString());
        item->setIcon(0,QIcon(info->m_showIcon));
    }
    item->setText(0,host->getPropertyValue("objectName").toString());
    item->setToolTip(0,host->getPropertyValue("objectName").toString());
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setExpanded(true);
    m_itemToHost.insert(item,host);
    m_hostToItem.insert(host,item);
    connect(host,SIGNAL(hostAdded(QAbstractHost*,int)),
            this,SLOT(addHost(QAbstractHost*)));
    connect(host,SIGNAL(hostRemoved(QAbstractHost*)),
            this,SLOT(removeHost(QAbstractHost*)));

    foreach(QAbstractHost *h,host->getChildrenHost())
    {
        insertHost(h);
    }
}

void QHostListView::selectHost(QAbstractHost *host)
{
    QTreeWidgetItem * item ;

    item = m_hostToItem.value(m_selectHost);
    if(item != NULL)
    {
        item->setSelected(false);
    }
    m_selectHost = host;
    item= m_hostToItem.value(m_selectHost);
    if(item != NULL)
    {
        item->setSelected(true);
    }
}

void QHostListView::clear()
{
    QMapIterator<QAbstractHost*,QTreeWidgetItem*> it(m_hostToItem);
    while(it.hasNext())
    {
        it.next();
        disconnect(it.key(),SIGNAL(hostAdded(QAbstractHost*,int)),
                   this,SLOT(addHost(QAbstractHost*)));
        disconnect(it.key(),SIGNAL(hostRemoved(QAbstractHost*)),
                   this,SLOT(removeHost(QAbstractHost*)));
    }
    m_itemToHost.clear();
    m_hostToItem.clear();
    m_selectHost = NULL;
    QBaseListView::clear();
}

void QHostListView::selectChanged()
{
    QMapIterator<QAbstractHost*,QTreeWidgetItem*> it(m_hostToItem);

    while(it.hasNext())
    {
        it.next();
        if(it.value()->isSelected())
        {
            if(m_selectHost != it.key())
            {
                m_selectHost = it.key();
                emit hostSelectChanged((QAbstractWidgetHost*)it.key());
            }
            return;
        }
    }
}

void QHostListView::addHost(QAbstractHost *host)
{
    insertHost(host);
    selectHost(host);
}

void QHostListView::removeHost(QAbstractHost *host)
{
    if(!m_hostToItem.keys().contains(host))
    {
        return;
    }
    disconnect(host,SIGNAL(hostAdded(QAbstractHost*,int)),
               this,SLOT(addHost(QAbstractHost*)));
    disconnect(host,SIGNAL(hostRemoved(QAbstractHost*)),
               this,SLOT(removeHost(QAbstractHost*)));
    m_itemToHost.remove(m_hostToItem.value(host));
    m_hostToItem.remove(host);
}
