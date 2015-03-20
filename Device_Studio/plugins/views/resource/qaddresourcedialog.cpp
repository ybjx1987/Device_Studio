#include "qaddresourcedialog.h"
#include "ui_qaddresourcedialog.h"

#include "qresourceitemwidget.h"
#include "qresourcerenamedialog.h"
#include "qsystemresourcedialog.h"
#include "../../../libs/platform/qbaseitemdelegate.h"
#include "../../../libs/platform/qbaselistview.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/platform/qsystemresourcemanager.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/kernel/resource/qresourcemanager.h"
#include "../../../libs/kernel/resource/qresourcefile.h"

#include <QFileDialog>
#include <QApplication>
#include <QHeaderView>
#include <QMessageBox>

QAddResourceDialog::QAddResourceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QAddResourceDialog),
    m_listview(new QBaseListView)
{
    ui->setupUi(this);
    setProperty("no-ManhattanStyle",true);
    ui->verticalLayout->insertWidget(0,m_listview,1);
    m_listview->setFrameStyle(QFrame::Box);
    m_listview->header()->hide();
    m_listview->setRootIsDecorated(true);
    ui->toolButton->setPopupMode(QToolButton::MenuButtonPopup);

    QAction * ac ;

    ac = new QAction(tr("From System"),this);
    ui->toolButton->addAction(ac);
    connect(ac,SIGNAL(triggered()),this,SLOT(fromSystem()));
    ui->toolButton->setDefaultAction(ac);
    ac = new QAction(tr("From Loacl"),this);
    ui->toolButton->addAction(ac);
    connect(ac,SIGNAL(triggered()),this,SLOT(fromLocal()));
}

QAddResourceDialog::~QAddResourceDialog()
{
    qDeleteAll(m_resourceToItem.keys());
    delete ui;
}

void QAddResourceDialog::fromSystem()
{
    QSystemResourceDialog dlg(this);
    dlg.exec();
    if(dlg.getRet() == 1)
    {
        foreach(QString str,dlg.getSelected())
        {
            if(!m_nameToInfo.keys().contains(qApp->applicationDirPath()+"/systemResources/"+str))
            {
                ResourceFileInfo *info = new ResourceFileInfo;
                info->m_path = str;
                info->m_type="system";
                info->m_sourcePath = qApp->applicationDirPath()+"/systemResources/"+str;
                addResource(info);
            }

        }
    }

    updateName();
}

void QAddResourceDialog::fromLocal()
{
    QStringList list = QFileDialog::getOpenFileNames(this,tr("Add Resource"),QDir::currentPath(),
                                 tr("All File(*.*)"));

    foreach(QString str,list)
    {
        int index = str.lastIndexOf("/");

        QString name = "user/"+str.mid(index+1);
        if(!m_nameToInfo.keys().contains(str))
        {
            ResourceFileInfo *info = new ResourceFileInfo;
            info->m_path = name;
            info->m_type="local";
            info->m_sourcePath = str;
            addResource(info);
        }

    }

    updateName();
}

void QAddResourceDialog::on_pushButton_2_clicked()
{
    close();
}

void QAddResourceDialog::on_pushButton_clicked()
{
    QMapIterator<ResourceFileInfo*,QTreeWidgetItem*> it(m_resourceToItem);

    while(it.hasNext())
    {
        it.next();

        QStringList list = getEnabledString(it.value());

        bool invalid = list.contains(it.key()->m_path.mid(it.key()->m_path.lastIndexOf("/")+1));
        if(invalid == true)
        {
            QMessageBox::warning(this,tr("Error"),tr("Some file name is invalid!"));
            return;
        }
    }
    QResourceManager * manager = QSoftCore::getInstance()->getProject()
            ->getResourceManager();
    it.toFront();
    while(it.hasNext())
    {
        it.next();
        QResourceFile *file = new QResourceFile(it.key()->m_path,it.key()->m_sourcePath);
        manager->addResource(file);
    }
    close();
}

void QAddResourceDialog::addResource(ResourceFileInfo *info)
{
    int index = info->m_path.lastIndexOf("/");
    QString group = info->m_path.left(index);
    QString name = info->m_path.mid(index+1);

    QTreeWidgetItem * parent = m_nameToGroup.value(group);

    if(parent == NULL)
    {
        parent = new QTreeWidgetItem(m_listview);
        parent->setText(0,group);
        parent->setToolTip(0,group);
        parent->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        parent->setData(0,DarkRole,true);
        parent->setExpanded(true);
        m_nameToGroup.insert(group,parent);
    }
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    QResourceItemWidget * wid = new QResourceItemWidget(info);
    connect(wid,SIGNAL(remove()),this,SLOT(itemRemove()));
    connect(wid,SIGNAL(rename()),this,SLOT(itemRename()));
    m_listview->setItemWidget(item,0,wid);
    wid->setText(name);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    m_resourceToItem.insert(info,item);
    m_itemToResource.insert(item,info);
    m_nameToInfo.insert(info->m_sourcePath,info);
}

void QAddResourceDialog::itemRemove()
{
    QResourceItemWidget * wid = (QResourceItemWidget*)sender();

    ResourceFileInfo * info = wid->getInfo();

    QTreeWidgetItem * item = m_resourceToItem.value(info);

    m_resourceToItem.remove(info);
    m_itemToResource.remove(item);
    m_nameToInfo.remove(info->m_sourcePath);

    QTreeWidgetItem * group = item->parent();

    delete item;
    delete info;

    if(group->childCount() == 0)
    {
        m_nameToGroup.remove(group->text(0));
        delete group;
    }

    updateName();
}

void QAddResourceDialog::itemRename()
{
    QResourceItemWidget * wid = (QResourceItemWidget*)sender();
    ResourceFileInfo * info = wid->getInfo();
    QResourceRenameDialog dlg(wid->getText(),getEnabledString(m_resourceToItem.value(info)),this);

    dlg.exec();

    if(dlg.getRet() ==1)
    {
        QString newName = dlg.getNewName();

        if(newName != wid->getText())
        {
            info->m_path = info->m_path.left(info->m_path.lastIndexOf("/"))+
                    "/"+newName;
            wid->setText(newName);

        }
    }

    updateName();
}

QStringList QAddResourceDialog::getEnabledString(QTreeWidgetItem * item)
{
    QString name = ((QResourceItemWidget*)m_listview->itemWidget(item,0))
            ->getText();
    QString group = item->parent()->text(0);
    QStringList list;

    QResourceManager * manager = QSoftCore::getInstance()->getProject()->getResourceManager();

    foreach(QResourceFile * file,manager->getResources())
    {
        QString temp = file->getPath();
        QString g = temp.left(temp.lastIndexOf("/"));
        if(g == group)
        {
            list.append(temp.mid(temp.lastIndexOf("/")+1));
        }
    }

    QTreeWidgetItem * gitem = item->parent();

    int count = gitem->childCount();

    for(int i =0;i<count;i++)
    {
        if(gitem->child(i)  == item)
        {
            continue;
        }
        QResourceItemWidget * wid = (QResourceItemWidget*)m_listview->itemWidget(gitem->child(i),0);
        list.append(wid->getText());
    }

    if(ui->checkBox->isChecked())
    {
        QStringList l = QSoftCore::getInstance()->getSystemResourceManager()->getSystemResource();
        foreach(QString str,l)
        {
            QString g = str.left(str.lastIndexOf("/"));
            QString n = str.mid(str.lastIndexOf("/")+1);

            if(g == group)
            {
                list.append(n);
            }
        }
    }

    return list;
}

void QAddResourceDialog::updateName()
{
    QMapIterator<ResourceFileInfo*,QTreeWidgetItem*> it(m_resourceToItem);

    while(it.hasNext())
    {
        it.next();

        QStringList list = getEnabledString(it.value());

        bool invalid = list.contains(it.key()->m_path.mid(it.key()->m_path.lastIndexOf("/")+1));

        ((QResourceItemWidget*)m_listview->itemWidget(it.value(),0))
                ->setInvalid(invalid);
    }
}
