#include "qnewtitledialog.h"
#include "ui_qnewtitledialog.h"

#include "../../../libs/platform/qvalidatoredit.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/kernel/host/qabstractwidgethost.h"
#include "../../../libs/kernel/host/qhostfactory.h"
#include "../../../libs/kernel/host/qwidgethost.h"

#include <QCompleter>

QNewTitleDialog::QNewTitleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewTitleDialog),
    m_nameEdit(new QValidatorEdit)
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(m_nameEdit,1);
    setProperty("no-ManhattanStyle",true);

    connect(ui->typeList,SIGNAL(currentIndexChanged(int)),this,SLOT(updateComplete()));

    QStringList list;

    list<<"none"<<"::add-line"<<"::add-page"<<"::chunk"
       <<"::down-arrow"<<"::down-button"<<"::drop-down"
      <<"::groove"<<"::indicator"<<"::handle"<<"::icon"
     <<"::item"<<"::left-arrow"<<"::menu-indicator"<<"::right-arrow"
    <<"::scroller"<<"::separator"<<"::sub-line"<<"::sub-page"
    <<"::title"<<"::up-arrow"<<"::up-button";

    ui->subControl->addItems(list);
    ui->subControl->setCurrentIndex(0);

    list.clear();

    list<<":active"<<":checked"<<":disabled"<<":editable"<<":edit-focus"
       <<":enabled"<<":focus"<<":horizontal"<<":hover"<<":indeterminate"
      <<":no-frame"<<":off"<<":on"<<":open"<<":pressed"<<":read-only"
     <<":selected"<<":unchecked"<<":vertical";

    foreach(QString str,list)
    {
        QCheckBox * box = new QCheckBox(str);
        box->setChecked(false);
        m_subControls.append(box);
    }
    int count = m_subControls.size();
    for(int i = 0;i<count;i++)
    {
        ui->gridLayout->addWidget(m_subControls.at(i),
                                  i/4,i%4);
    }

    setFixedSize(this->minimumSize());

    updateComplete();
}

QNewTitleDialog::~QNewTitleDialog()
{
    m_nameEdit->setCompleter(NULL);
    delete ui;
}

void QNewTitleDialog::on_okBtn_clicked()
{

}

void QNewTitleDialog::on_cancleBtn_clicked()
{
    close();
}

void QNewTitleDialog::updateComplete()
{
    m_nameEdit->setValue("");
    QStringList list;

    if(ui->typeList->currentIndex() == 0)
    {
        QList<QAbstractWidgetHost*> forms = QSoftCore::getInstance()->getProject()
                ->getForms();

        while(forms.size()>0)
        {
            QAbstractWidgetHost * host = forms.takeFirst();

            list.append(host->getPropertyValue("objectName").toString());

            foreach(QAbstractHost * h,host->getChildrenHost())
            {
                forms.append((QAbstractWidgetHost*)h);
            }
        }
    }
    else
    {
        QList<QAbstractHostInfo*> infos = QHostFactory::getHostInfo();
        foreach(QAbstractHostInfo * info,infos)
        {
            if(info->m_type == "Widget")
            {
                QWidgetHostInfo *winfo = (QWidgetHostInfo*)info;
                list.append(winfo->m_name);
            }
            else
            {
                list.append(info->m_type);
            }
        }
    }

    QCompleter *pleter = new QCompleter(list);
    m_nameEdit->setCompleter(pleter);
}
