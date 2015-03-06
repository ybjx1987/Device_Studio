#include "qstylesheetitemwidget.h"

#include "qitemendwidget.h"
#include "qtitlewidget.h"

QStyleSheetItemWidget::QStyleSheetItemWidget(QWidget *parent) :
    QWidget(parent),
    m_titleWidget(new QTitleWidget),
    m_endWidget(new QItemEndWidget),
    m_layout(new QVBoxLayout)
{
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    m_layout->addWidget(m_titleWidget);
    m_layout->addWidget(m_endWidget);

    setLayout(m_layout);

    updateHeight();
}

QStyleSheetItemWidget::~QStyleSheetItemWidget()
{

}

void QStyleSheetItemWidget::updateHeight()
{
    int h = 0;
    h += m_titleWidget->height();
    h += m_endWidget->height();

    setFixedHeight(h);
}
