#include "qlanguagewidget.h"

#include "../../../libs/platform/styledbar.h"

#include <QVBoxLayout>

QLanguageWidget::QLanguageWidget(QWidget* parent):
    QAbstractPageWidget(parent),
    m_languageBar(new StyledBar)
{
    QVBoxLayout *v = new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addWidget(m_languageBar);
    setLayout(v);
}

