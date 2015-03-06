#include "qdeletestylesheetdialog.h"
#include "ui_qdeletestylesheetdialog.h"

#include "../../../libs/platform/qbaselistview.h"
#include "../../../libs/kernel/stylesheet/qstylesheetmanager.h"
#include "../../../libs/kernel/stylesheet/qstylesheetgroup.h"

#include <QHeaderView>
#include <QContextMenuEvent>
#include <QMenu>

QDeleteStyleSheetDialog::QDeleteStyleSheetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDeleteStyleSheetDialog),
    m_listView(new QBaseListView)
{
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0,m_listView,1);
    m_listView->setFrameStyle(QFrame::Box);
    m_listView->header()->hide();
    m_listView->installEventFilter(this);
    connect(m_listView,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(itemClicked(QTreeWidgetItem*)));
}

QDeleteStyleSheetDialog::~QDeleteStyleSheetDialog()
{
    delete ui;
}

void QDeleteStyleSheetDialog::on_okBtn_clicked()
{
    QMapIterator<QTreeWidgetItem*,QStyleSheetGroup*>    it(m_itemToGroup);

    while(it.hasNext())
    {
        it.next();
        if(it.key()->checkState(0) == Qt::Checked)
        {
            m_manager->delGroup(it.value());
        }
    }

    close();
}

void QDeleteStyleSheetDialog::on_cancelBtn_clicked()
{
    close();
}

void QDeleteStyleSheetDialog::init(QStyleSheetManager *manager)
{
    m_manager = manager;

    foreach(QStyleSheetGroup * group,manager->getGroups())
    {
        QTreeWidgetItem * item = new QTreeWidgetItem(m_listView);
        item->setText(0,group->getName());
        item->setToolTip(0,group->getName());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setCheckState(0,Qt::Unchecked);
        m_itemToGroup.insert(item,group);
    }
}

void QDeleteStyleSheetDialog::itemClicked(QTreeWidgetItem *item)
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

bool QDeleteStyleSheetDialog::eventFilter(QObject *o, QEvent *e)
{
    if(o == m_listView)
    {
        if(e->type() == QEvent::ContextMenu)
        {
            QContextMenuEvent *event = (QContextMenuEvent*)e;

            QAction * ac;

            QMenu menu(this);

            ac = menu.addAction(tr("Select All"));
            connect(ac,SIGNAL(triggered()),this,SLOT(selectAll()));

            ac = menu.addAction(tr("Clear All"));
            connect(ac,SIGNAL(triggered()),this,SLOT(clearAll()));

            menu.exec(event->globalPos());
            return true;
        }
    }
    return false;
}

void QDeleteStyleSheetDialog::selectAll()
{
    QMapIterator<QTreeWidgetItem*,QStyleSheetGroup*>    it(m_itemToGroup);

    while(it.hasNext())
    {
        it.next();
        it.key()->setCheckState(0,Qt::Checked);
    }
}

void QDeleteStyleSheetDialog::clearAll()
{
    QMapIterator<QTreeWidgetItem*,QStyleSheetGroup*>    it(m_itemToGroup);

    while(it.hasNext())
    {
        it.next();
        it.key()->setCheckState(0,Qt::Unchecked);
    }
}
