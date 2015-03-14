#include "qsystemresourcedialog.h"
#include "ui_qsystemresourcedialog.h"

#include "../../../libs/platform/qbaseitemdelegate.h"
#include "../../../libs/platform/qbaselistview.h"

#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/platform/qsystemresourcemanager.h"

#include <QHeaderView>

QSystemResourceDialog::QSystemResourceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSystemResourceDialog),
    m_resourceList(new QBaseListView)
{
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0,m_resourceList,1);

    m_resourceList->header()->hide();
    m_resourceList->setFrameStyle(QFrame::Box);

    updateSystemResource();

    connect(QSoftCore::getInstance()->getSystemResourceManager(),
            SIGNAL(needUpdate()),this,SLOT(updateSystemResource()));
    m_resourceList->setRootIsDecorated(true);

    connect(m_resourceList,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(itemClicked(QTreeWidgetItem*)));
}

QSystemResourceDialog::~QSystemResourceDialog()
{
    delete ui;
}

void QSystemResourceDialog::on_pushButton_2_clicked()
{

}

void QSystemResourceDialog::on_pushButton_clicked()
{
    close();
}

void QSystemResourceDialog::updateSystemResource()
{
    QSystemResourceManager * manager = QSoftCore::getInstance()->getSystemResourceManager();
    QStringList list = manager->getSystemResource();

    QStringList groups;

    foreach(QString str,list)
    {
        int index = str.lastIndexOf("/");
        QString s= str.left(index);
        if(!groups.contains(s))
        {
            groups.append(s);
        }
    }

    while(groups.size() < m_resourceList->topLevelItemCount())
    {
        delete m_resourceList->takeTopLevelItem(groups.size());
    }

    while(groups.size() > m_resourceList->topLevelItemCount())
    {
        QTreeWidgetItem * item = new QTreeWidgetItem(m_resourceList);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setData(0,DarkRole,true);
    }
    m_nameToGroup.clear();
    for(int i=0;i<groups.size();i++)
    {
        QTreeWidgetItem *item= m_resourceList->topLevelItem(i);
        item->setText(0,groups.at(i));
        item->setToolTip(0,groups.at(i));
        m_nameToGroup.insert(groups.at(i),item);
        item->setExpanded(true);
        qDeleteAll(item->takeChildren());
    }
    QMapIterator<QString,bool> it(m_checked);

    while(it.hasNext())
    {
        it.next();
        if(!list.contains(it.key()))
        {
            m_checked.insert(it.key(),false);
        }
    }

    foreach(QString str,list)
    {
        int index = str.lastIndexOf("/");
        QString s= str.left(index);
        QString n = str.mid(index+1);

        QTreeWidgetItem * p = m_nameToGroup.value(s);
        QTreeWidgetItem * item = new QTreeWidgetItem(p);
        item->setText(0,n);
        item->setToolTip(0,n);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setCheckState(0,m_checked.value(str,false)?Qt::Checked:Qt::Unchecked);
    }

    updateCheck();
}

void QSystemResourceDialog::updateCheck()
{
    int count = m_resourceList->topLevelItemCount();
    for(int i =0;i<count;i++)
    {
        QTreeWidgetItem * item = m_resourceList->topLevelItem(i);
        int cc=item->childCount();
        int c = 0;
        for(int j= 0;j<cc;j++)
        {
            if(item->child(j)->checkState(0) == Qt::Checked)
            {
                c++;
            }
        }
        if(c==0)
        {
            item->setCheckState(0,Qt::Unchecked);
        }
        else if(c < cc)
        {
            item->setCheckState(0,Qt::PartiallyChecked);
        }
        else
        {
            item->setCheckState(0,Qt::Checked);
        }
    }
}

void QSystemResourceDialog::itemClicked(QTreeWidgetItem *item)
{
    if(m_nameToGroup.values().contains(item))
    {
        int count = item->childCount();
        for(int i= 0;i<count;i++)
        {
            QTreeWidgetItem * c = item->child(0);
            if(c->checkState(0) == Qt::Checked)
            {
                m_checked.insert(c->text(0),false);
                c->setCheckState(0,Qt::Unchecked);
            }
            else
            {
                m_checked.insert(c->text(0),true);
                c->setCheckState(0,Qt::Checked);
            }
        }
    }
    else
    {
        if(item->checkState(0) == Qt::Checked)
        {
            m_checked.insert(item->text(0),false);
            item->setCheckState(0,Qt::Unchecked);
        }
        else
        {
            m_checked.insert(item->text(0),true);
            item->setCheckState(0,Qt::Checked);
        }
    }
    updateCheck();
}
