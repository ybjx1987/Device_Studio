#include "qabstractpagewidget.h"

#include "qsoftcore.h"

#include "../kernel/qproject.h"

QAbstractPageWidget::QAbstractPageWidget(QWidget *parent) :
    QWidget(parent)
{
    connect(QSoftCore::getInstance()->getProject(),
            SIGNAL(projectOpened()),this,SLOT(projectOpened()));
    connect(QSoftCore::getInstance()->getProject(),
            SIGNAL(projectClosed()),this,SLOT(projectClosed()));
}

void QAbstractPageWidget::setVisible(bool visible)
{
    emit select(visible);
    QWidget::setVisible(visible);
}

void QAbstractPageWidget::projectOpened()
{

}

void QAbstractPageWidget::projectClosed()
{

}
