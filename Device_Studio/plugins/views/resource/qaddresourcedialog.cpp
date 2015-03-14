#include "qaddresourcedialog.h"
#include "ui_qaddresourcedialog.h"

#include "qresourceitemwidget.h"
#include "qsystemresourcedialog.h"
#include "../../../libs/platform/qbaseitemdelegate.h"
#include "../../../libs/platform/qbaselistview.h"
#include "../../../libs/platform/qrenamedialog.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/platform/qsystemresourcemanager.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/kernel/resource/qresourcemanager.h"
#include "../../../libs/kernel/resource/qresourcefile.h"

#include <QFileDialog>
#include <QApplication>
#include <QHeaderView>

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
            if(!m_nameToInfo.keys().contains(str))
            {
                ResourceFileInfo *info = new ResourceFileInfo;
                info->m_path = str;
                info->m_type="system";
                addResource(info);
            }

        }
    }
}

void QAddResourceDialog::fromLocal()
{
    QStringList list = QFileDialog::getOpenFileNames(this,tr("Add Resource"),QDir::currentPath(),
                                 tr("All File(*.*)"));

    foreach(QString str,list)
    {
        int index = str.lastIndexOf("/");

        QString name = "user/"+str.mid(index+1);
        if(!m_nameToInfo.keys().contains(name))
        {
            ResourceFileInfo *info = new ResourceFileInfo;
            info->m_path = name;
            info->m_type="local";
            addResource(info);
        }

    }
}

void QAddResourceDialog::on_pushButton_2_clicked()
{
    close();
}

void QAddResourceDialog::on_pushButton_clicked()
{

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
    m_nameToInfo.insert(info->m_path,info);
}

void QAddResourceDialog::itemRemove()
{
    QResourceItemWidget * wid = (QResourceItemWidget*)sender();

    ResourceFileInfo * info = wid->getInfo();

    QTreeWidgetItem * item = m_resourceToItem.value(info);

    m_resourceToItem.remove(info);
    m_itemToResource.remove(item);
    m_nameToInfo.remove(info->m_path);

    QTreeWidgetItem * group = item->parent();

    delete item;
    delete info;

    if(group->childCount() == 0)
    {
        m_nameToGroup.remove(group->text(0));
        delete group;
    }
}

void QAddResourceDialog::itemRename()
{
    QRenameDialog dlg(this);

    QResourceItemWidget * wid = (QResourceItemWidget*)sender();
    ResourceFileInfo * info = wid->getInfo();
    QTreeWidgetItem * item = m_resourceToItem.value(info);
    dlg.setOldName(wid->getText());

    dlg.setNameList(getEnabledString(info->m_path));


    dlg.exec();
}

QStringList QAddResourceDialog::getEnabledString(const QString &path)
{
    QString name = path.mid(path.lastIndexOf("/")+1);
    QString group = path.left(path.lastIndexOf("/"));
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

    QTreeWidgetItem * gitem = m_nameToGroup.value(group);

    int count = gitem->childCount();

    for(int i =0;i<count;i++)
    {
        QResourceItemWidget * wid = (QResourceItemWidget*)m_listview->itemWidget(gitem->child(i),0);
        if(wid->getText() != name)
        {
            list.append(wid->getText());
        }
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
