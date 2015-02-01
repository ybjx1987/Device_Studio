#include "qabstractpagewidget.h"

QAbstractPageWidget::QAbstractPageWidget(QWidget *parent) : QWidget(parent)
{

}

void QAbstractPageWidget::setVisible(bool visible)
{
    emit select(visible);
    QWidget::setVisible(visible);
}

