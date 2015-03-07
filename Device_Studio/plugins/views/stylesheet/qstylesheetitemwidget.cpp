#include "qstylesheetitemwidget.h"

#include "qitemendwidget.h"
#include "qtitlewidget.h"
#include "qitempropertylistview.h"
#include "qnewtitledialog.h"

#include "../../../libs/kernel/stylesheet/qstylesheetitem.h"
#include "../../../libs/kernel/stylesheet/qstylesheetitemtitle.h"

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
    connect(m_titleWidget,SIGNAL(delTitle(QString)),
            this,SLOT(delTitle(QString)));
    connect(m_titleWidget,SIGNAL(delItem()),
            this,SIGNAL(delItem()));

    foreach(QStyleSheetItemTitle *title,m_sheetItem->getTitles())
    {
        m_titleWidget->addTitle(title->getText());
    }

    connect(m_sheetItem,SIGNAL(titleAdded(QStyleSheetItemTitle*)),
            this,SLOT(titleAdded(QStyleSheetItemTitle*)));
    connect(m_sheetItem,SIGNAL(titleDeled(QStyleSheetItemTitle*)),
            this,SLOT(titleDeled(QStyleSheetItemTitle*)));

    setMinimumWidth(600);
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
    QNewTitleDialog dlg(m_sheetItem,this);
    dlg.exec();
}

void QStyleSheetItemWidget::titleAdded(QStyleSheetItemTitle *title)
{
    m_titleWidget->addTitle(title->getText());
}

void QStyleSheetItemWidget::titleDeled(QStyleSheetItemTitle *title)
{
    m_titleWidget->removeTitle(title->getText());
}

void QStyleSheetItemWidget::delTitle(const QString &title)
{
    foreach(QStyleSheetItemTitle *t,m_sheetItem->getTitles())
    {
        if(t->getText() == title)
        {
            m_sheetItem->delTitle(t);
            return;
        }
    }
}
