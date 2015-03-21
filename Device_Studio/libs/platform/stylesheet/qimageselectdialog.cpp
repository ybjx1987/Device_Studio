#include "qimageselectdialog.h"
#include "ui_qimageselectdialog.h"

#include "../qprojectresourceview.h"

#include <QHBoxLayout>

QImageSelectDialog::QImageSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QImageSelectDialog),
    m_resourceView(new QProjectResourceView),
    m_resourceFile(NULL)
{
    ui->setupUi(this);

    QHBoxLayout *hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(0);
    hb->addWidget(m_resourceView);
    setLayout(hb);

    m_resourceView->setFocusPolicy(Qt::StrongFocus);

    connect(m_resourceView,SIGNAL(fileSelect(QResourceFile*)),
            this,SLOT(select(QResourceFile*)));
}

QImageSelectDialog::~QImageSelectDialog()
{
    delete ui;
}

void QImageSelectDialog::select(QResourceFile *file)
{
    m_resourceFile = file;
    close();
}

QResourceFile * QImageSelectDialog::getSelect()
{
    return m_resourceFile;
}
