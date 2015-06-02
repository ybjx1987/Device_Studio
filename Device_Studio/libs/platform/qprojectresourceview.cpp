#include "qprojectresourceview.h"

#include "qsoftcore.h"
#include "qbaseitemdelegate.h"

#include "../kernel/qproject.h"
#include "../kernel/resource/qresourcemanager.h"
#include "../kernel/resource/qresourcefile.h"

#include <QHeaderView>

QProjectResourceView::QProjectResourceView(QWidget *parent) :
    QBaseListView(parent)
{
    QResourceManager * manager = QSoftCore::getInstance()->getProject()
            ->getResourceManager();

    setRootIsDecorated(true);

    header()->hide();

    QString group;
    QString name;
    int index;
    foreach(QResourceFile * file,manager->getResources())
    {
        index = file->getPath().lastIndexOf("/");
        if(index > 0)
        {
            group = file->getPath().left(index);
            name = file->getPath().mid(index + 1);
            QTreeWidgetItem * g = m_nameToGroup.value(group);
            if(g == NULL)
            {
                g = new QTreeWidgetItem(this);
                g->setText(0,group);
                g->setToolTip(0,group);
                g->setData(0,DarkRole,true);
                g->setExpanded(true);
                g->setFlags(Qt::ItemIsEnabled);
                m_nameToGroup.insert(group,g);
            }

            QTreeWidgetItem * item = new QTreeWidgetItem(g);
            item->setText(0,name);
            item->setToolTip(0,name);
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            m_itemToFile.insert(item,file);
        }
    }

    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this,SLOT(doubleClickItem(QTreeWidgetItem*)));
}

QProjectResourceView::~QProjectResourceView()
{

}

void QProjectResourceView::doubleClickItem(QTreeWidgetItem *item)
{
    QResourceFile * file = m_itemToFile.value(item);

    if(file != NULL)
    {
        emit fileSelect(file);
    }
}
