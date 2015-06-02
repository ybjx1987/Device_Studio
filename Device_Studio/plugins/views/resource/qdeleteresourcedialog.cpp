#include "qdeleteresourcedialog.h"
#include "ui_qdeleteresourcedialog.h"

#include "../../../libs/platform/qbaselistview.h"
#include "../../../libs/platform/qbaseitemdelegate.h"

#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/kernel/resource/qresourcemanager.h"
#include "../../../libs/kernel/resource/qresourcefile.h"

QDeleteResourceDialog::QDeleteResourceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDeleteResourceDialog),
    m_listView(new QBaseListView)
{
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0,m_listView,1);

    m_listView->header()->hide();
    m_listView->setFrameStyle(QFrame::Box);
    m_listView->setRootIsDecorated(true);

    QResourceManager * manager = QSoftCore::getInstance()->getProject()
            ->getResourceManager();
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
                g = new QTreeWidgetItem(m_listView);
                g->setText(0,group);
                g->setToolTip(0,group);
                g->setData(0,DarkRole,true);
                g->setExpanded(true);
                g->setFlags(Qt::ItemIsEnabled);
                g->setCheckState(0,Qt::Unchecked);
                m_nameToGroup.insert(group,g);
            }

            QTreeWidgetItem * item = new QTreeWidgetItem(g);
            item->setText(0,name);
            item->setToolTip(0,name);
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            item->setCheckState(0,Qt::Unchecked);
            m_itemToFile.insert(item,file);
        }
    }

    connect(m_listView,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(itemClicked(QTreeWidgetItem*)));
}

QDeleteResourceDialog::~QDeleteResourceDialog()
{
    delete ui;
}

void QDeleteResourceDialog::itemClicked(QTreeWidgetItem *item)
{
    if(m_itemToFile.keys().contains(item))
    {
        if(item->checkState(0) == Qt::Checked)
        {
            item->setCheckState(0,Qt::Unchecked);
        }
        else
        {
            item->setCheckState(0,Qt::Checked);
        }

        int count = 0;

        QTreeWidgetItem * g = item->parent();

        for(int i= 0;i<g->childCount();i++)
        {
            if(g->child(i)->checkState(0) == Qt::Checked)
            {
                count ++;
            }
        }

        if(count == 0)
        {
            g->setCheckState(0,Qt::Unchecked);
        }
        else if(count < g->childCount())
        {
            g->setCheckState(0,Qt::PartiallyChecked);
        }
        else
        {
            g->setCheckState(0,Qt::Checked);
        }
    }
    else
    {
        if(item->checkState(0) == Qt::Checked)
        {
            item->setCheckState(0,Qt::Unchecked);
        }
        else
        {
            item->setCheckState(0,Qt::Checked);
        }

        int count = item->childCount();

        for(int i= 0;i<count;i++)
        {
            item->child(i)->setCheckState(0,item->checkState(0));
        }
    }
}

void QDeleteResourceDialog::on_cancelBtn_clicked()
{
    close();
}

void QDeleteResourceDialog::on_okBtn_clicked()
{
    QMapIterator<QTreeWidgetItem*,QResourceFile*> it(m_itemToFile);

    while(it.hasNext())
    {
        it.next();
        if(it.key()->checkState(0) == Qt::Checked)
        {
            m_selectFile.append(it.value());
        }
    }

    close();
}

QList<QResourceFile*> QDeleteResourceDialog::getSelectFile()
{
    return m_selectFile;
}
