#include "qresourcelistview.h"

#include "../../../libs/kernel/resource/qresourcemanager.h"
#include "../../../libs/kernel/resource/qresourcefile.h"
#include "../../../libs/platform/qbaseitemdelegate.h"

QResourceListView::QResourceListView(QWidget* parent):
    QBaseListView(parent)
{
    setRootIsDecorated(true);
    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(itemSelectChanged()));
}

void QResourceListView::init(QResourceManager *manager)
{
    clear();
    connect(manager,SIGNAL(resourceAdded(QResourceFile*)),
            this,SLOT(resourceAdded(QResourceFile*)));
    connect(manager,SIGNAL(resourceDeled(QResourceFile*)),
            this,SLOT(resourceDeled(QResourceFile*)));

    foreach(QResourceFile * resource,manager->getResources())
    {
        resourceAdded(resource);
    }
}

void QResourceListView::resourceAdded(QResourceFile *resource)
{
    QString path = resource->getPath();

    int index = path.lastIndexOf("/");
    if(index > 0)
    {
        QString firstName = path.left(index);
        QString secondName = path.mid(index + 1);

        QTreeWidgetItem * parent = m_nameToGroup.value(firstName);
        if(parent == NULL)
        {
            parent = new QTreeWidgetItem(this);
            parent->setText(0,firstName);
            parent->setToolTip(0,firstName);
            parent->setData(0,DarkRole,true);
            parent->setFlags(Qt::ItemIsEnabled);
            parent->setExpanded(true);
            m_nameToGroup.insert(firstName,parent);
        }

        QTreeWidgetItem * item = new QTreeWidgetItem(parent);
        item->setText(0,secondName);
        item->setToolTip(0,secondName);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        m_itemToResource.insert(item,resource);
        m_resourceToItem.insert(resource,item);

        if(m_itemToResource.size() == 1)
        {
            item->setSelected(true);
        }
    }
}

void QResourceListView::resourceDeled(QResourceFile *resource)
{
    QString path = resource->getPath();

    int index = path.lastIndexOf("/");
    if(index > 0)
    {
        QString firstName = path.left(index);

        QTreeWidgetItem * item = m_resourceToItem.value(resource);

        m_resourceToItem.remove(resource);
        if(item != NULL)
        {
            delete item;
        }

        item = m_nameToGroup.value(firstName);
        if(item != NULL)
        {
            if(item->childCount() == 0)
            {
                delete item;
            }
        }
    }
}

void QResourceListView::itemSelectChanged()
{
    QList<QTreeWidgetItem*> items = selectedItems();
    if(items.size() > 0)
    {
        emit resourceSelect(m_itemToResource.value(items.first()));
    }
    else
    {
        emit resourceSelect(NULL);
    }
}

void QResourceListView::clear()
{
    m_nameToGroup.clear();
    m_resourceToItem.clear();
    m_itemToResource.clear();
    QBaseListView::clear();
}
