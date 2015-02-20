#include "qdeleteitemdialog.h"
#include "ui_qdeleteitemdialog.h"

#include "../../../libs/platform/qbaselistview.h"

QDeleteItemDialog::QDeleteItemDialog(const QStringList &list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDeleteItemDialog),
    m_listView(new QBaseListView)
{
    ui->setupUi(this);

    ui->verticalLayout->insertWidget(0,m_listView,1);

    m_listView->setFrameStyle(QFrame::Box);

    m_listView->setHeaderLabels(QStringList()<<tr("Keyword"));

    foreach(QString str,list)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(m_listView);
        item->setText(0,str);
        item->setToolTip(0,str);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m_keyToItem.insert(str,item);
        m_itemToKey.insert(item,str);
        item->setCheckState(0,Qt::Unchecked);
    }

    connect(m_listView,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(itemClicked(QTreeWidgetItem*)));
}

QDeleteItemDialog::~QDeleteItemDialog()
{
    delete ui;
}

void QDeleteItemDialog::itemClicked(QTreeWidgetItem *item)
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

QStringList QDeleteItemDialog::getSelection()
{
    return m_selectList;
}

void QDeleteItemDialog::on_okBtn_clicked()
{
    QMapIterator<QString,QTreeWidgetItem*> it(m_keyToItem);

    while(it.hasNext())
    {
        it.next();
        if(it.value()->checkState(0) == Qt::Checked)
        {
            m_selectList.append(it.key());
        }
    }

    close();
}

void QDeleteItemDialog::on_cancelBtn_clicked()
{
    close();
}
