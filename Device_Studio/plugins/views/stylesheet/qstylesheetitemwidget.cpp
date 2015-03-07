#include "qstylesheetitemwidget.h"

#include "qitemendwidget.h"
#include "qtitlewidget.h"
#include "qitempropertylistview.h"
#include "qnewtitledialog.h"

QStyleSheetItemWidget::QStyleSheetItemWidget(QStyleSheetItem * item,QWidget *parent) :
    QWidget(parent),
    m_titleWidget(new QTitleWidget),
    m_endWidget(new QItemEndWidget),
    m_propertyListView(new QItemPropertyListView),
    m_layout(new QVBoxLayout),
    m_sheetItem(item)
{
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    m_layout->addWidget(m_titleWidget);
    m_layout->addWidget(m_propertyListView);
    m_layout->addWidget(m_endWidget);

    setLayout(m_layout);

    updateHeight();

    connect(m_titleWidget,SIGNAL(addTitle()),this,SLOT(addTitle()));
}

QStyleSheetItemWidget::~QStyleSheetItemWidget()
{

}

void QStyleSheetItemWidget::updateHeight()
{
    m_propertyListView->updateHeight();
    int h = 0;
    h += m_titleWidget->height();
    h += m_propertyListView->height();
    h += m_endWidget->height();
    setFixedHeight(h);
}

void QStyleSheetItemWidget::addTitle()
{
    QNewTitleDialog dlg(this);
    dlg.exec();
}
