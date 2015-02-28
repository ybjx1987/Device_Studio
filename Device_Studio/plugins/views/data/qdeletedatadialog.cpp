#include "qdeletedatadialog.h"
#include "ui_qdeletedatadialog.h"

#include "../../../libs/platform/qbaselistview.h"
#include "../../../libs/platform/qbaseitemdelegate.h"

#include "../../../libs/kernel/data/qabstractdatahost.h"
#include "../../../libs/kernel/data/qdatagroup.h"
#include "../../../libs/kernel/data/qdatamanager.h"

#include <QHeaderView>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>

QDeleteDataDialog::QDeleteDataDialog(QDataManager* manager,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDeleteDataDialog),
    m_listView(new QBaseListView),
    m_dataManager(manager)
{
    ui->setupUi(this);

    ui->verticalLayout->insertWidget(0,m_listView,1);

    m_listView->setFrameStyle(QFrame::Box);
    m_listView->header()->hide();

    QList<QDataGroup*> groups = m_dataManager->getGroups();

    foreach(QDataGroup * g,groups)
    {
        QList<QAbstractDataHost*> datas = g->getDatas();
        if(datas.size()>0)
        {
            QTreeWidgetItem * gitem = new QTreeWidgetItem(m_listView);
            gitem->setText(0,g->getGroupName());
            gitem->setData(0,DarkRole,true);
            gitem->setExpanded(true);
            gitem->setIcon(0,m_listView->getExpandIcon());
            m_itemToGroup.insert(gitem,g);

            foreach(QAbstractDataHost * data,datas)
            {
                QTreeWidgetItem * ditem = new QTreeWidgetItem(gitem);
                ditem->setText(0,data->getPropertyValue("objectName").toString());
                ditem->setCheckState(0,Qt::Unchecked);
                ditem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                m_itemToData.insert(ditem,data);
            }
        }
    }
    connect(m_listView,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(itemClicked(QTreeWidgetItem*)));

    m_listView->installEventFilter(this);

    QAction * ac;

    ac = new QAction(tr("Select All"),this);
    connect(ac,SIGNAL(triggered()),this,SLOT(selectAll()));
    m_actions.append(ac);

    ac = new QAction(tr("Clear All"),this);
    connect(ac,SIGNAL(triggered()),this,SLOT(clearAll()));
    m_actions.append(ac);
}

QDeleteDataDialog::~QDeleteDataDialog()
{
    delete ui;
}

void QDeleteDataDialog::itemClicked(QTreeWidgetItem *item)
{
    if(m_itemToData.keys().contains(item))
    {
        if(item->checkState(0) == Qt::Checked)
        {
            item->setCheckState(0,Qt::Unchecked);
        }
        else
        {
            item->setCheckState(0,Qt::Checked);
        }
    }
}

void QDeleteDataDialog::showMenu(const QPoint &pt)
{
    QMenu menu(this);

    menu.addActions(m_actions);

    menu.exec(pt);
}

bool QDeleteDataDialog::eventFilter(QObject *o, QEvent *e)
{
    if(o == m_listView)
    {
        if(e->type() == QEvent::ContextMenu)
        {
            QContextMenuEvent *event = (QContextMenuEvent*)e;

            showMenu(event->globalPos());
            return true;
        }
    }

    return false;
}

void QDeleteDataDialog::selectAll()
{
    QMapIterator<QTreeWidgetItem*,QAbstractDataHost*> it(m_itemToData);

    while(it.hasNext())
    {
        it.next();
        it.key()->setCheckState(0,Qt::Checked);
    }
}

void QDeleteDataDialog::clearAll()
{
    QMapIterator<QTreeWidgetItem*,QAbstractDataHost*> it(m_itemToData);

    while(it.hasNext())
    {
        it.next();
        it.key()->setCheckState(0,Qt::Unchecked);
    }
}

void QDeleteDataDialog::on_cancelBtn_clicked()
{
    close();
}

void QDeleteDataDialog::on_okBtn_clicked()
{
    QMapIterator<QTreeWidgetItem*,QAbstractDataHost*> it(m_itemToData);

    while(it.hasNext())
    {
        it.next();
        if(it.key()->checkState(0) == Qt::Checked)
        {
            QDataGroup * g = m_itemToGroup.value(it.key()->parent());
            g->delData(it.value());
        }
    }

    close();
}
