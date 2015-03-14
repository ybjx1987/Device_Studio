#include "qresourceitemwidget.h"

#include "qaddresourcedialog.h"

#include "../../../libs/platform/qtoolbarbutton.h"

#include <QHBoxLayout>
#include <QAction>

QResourceItemWidget::QResourceItemWidget(ResourceFileInfo *info,QWidget *parent) :
    QWidget(parent),
    m_textLabel(new QLabel),
    m_info(info)
{
    QHBoxLayout *hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(1);
    hb->addWidget(m_textLabel);
    QAction * ac;
    QToolBarButton *button;
    ac = new QAction(QIcon(":/inner/images/edit.png")
                         ,tr("Rename"),this);
    m_renameButton = new QToolBarButton(ac);
    hb->addWidget(m_renameButton);
    connect(ac,SIGNAL(triggered()),this,SIGNAL(rename()));
    m_renameButton->setVisible(false);

    ac = new QAction(QIcon(":/inner/images/delete_item.png")
                     ,tr("Remove Resource"),this);
    m_removeButton = new QToolBarButton(ac);
    connect(ac,SIGNAL(triggered()),this,SIGNAL(remove()));
    hb->addWidget(m_removeButton);
    m_removeButton->setVisible(false);

    setLayout(hb);
}

QResourceItemWidget::~QResourceItemWidget()
{

}

ResourceFileInfo * QResourceItemWidget::getInfo()
{
    return m_info;
}

void QResourceItemWidget::setText(const QString &text)
{
    m_textLabel->setText(text);
    m_textLabel->setToolTip(text);
}

QString QResourceItemWidget::getText()
{
    return m_textLabel->text();
}

void QResourceItemWidget::enterEvent(QEvent *)
{
    m_removeButton->setVisible(true);
    m_renameButton->setVisible(m_info->m_type == "local");
}

void QResourceItemWidget::leaveEvent(QEvent *)
{
    m_removeButton->setVisible(false);
    m_renameButton->setVisible(false);
}

void QResourceItemWidget::setInvalid(bool invalid)
{
    if(invalid)
    {
        m_textLabel->setStyleSheet("color:rgb(255,0,0);");
    }
    else
    {
        m_textLabel->setStyleSheet("color:rgb(0,0,0);");
    }
}
