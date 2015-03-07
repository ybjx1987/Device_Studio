#include "qonegroupwidget.h"

#include "qstylesheetitemwidget.h"

#include "../../../libs/kernel/stylesheet/qstylesheetitem.h"
#include "../../../libs/kernel/stylesheet/qstylesheetgroup.h"

#include <QPainter>

QOneGroupWidget::QOneGroupWidget(QStyleSheetGroup * group,QWidget *parent) :
    QWidget(parent),
    m_group(group),
    m_layout(new QVBoxLayout)
{

    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    m_layout->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,
                                            QSizePolicy::Expanding));
    setLayout(m_layout);

    foreach(QStyleSheetItem * item,group->getItems())
    {
        QStyleSheetItemWidget * wid = new QStyleSheetItemWidget(item,this);
        m_itemToWidget.insert(item,wid);
        m_layout->insertWidget(m_layout->count()-1,wid);
        connect(wid,SIGNAL(delItem()),this,SLOT(delItem()));
    }

    connect(group,SIGNAL(itemAdded(QStyleSheetItem*)),
            this,SLOT(itemAdded(QStyleSheetItem*)));
    connect(group,SIGNAL(itemDeled(QStyleSheetItem*)),
            this,SLOT(itemDeled(QStyleSheetItem*)));
}

QOneGroupWidget::~QOneGroupWidget()
{
    clear();
}

void QOneGroupWidget::itemAdded(QStyleSheetItem *item)
{
    QStyleSheetItemWidget * wid = new QStyleSheetItemWidget(item,this);

    m_itemToWidget.insert(item,wid);
    m_layout->insertWidget(m_layout->count()-1,wid);
    connect(wid,SIGNAL(delItem()),this,SLOT(delItem()));

    updateRect();
}

void QOneGroupWidget::itemDeled(QStyleSheetItem *item)
{
    QStyleSheetItemWidget * wid = m_itemToWidget.value(item);
    if(wid != NULL)
    {
        m_itemToWidget.remove(item);
        delete wid;
        updateRect();
    }
}

void QOneGroupWidget::updateRect()
{
    int h = 0;

    QMapIterator<QStyleSheetItem*,QStyleSheetItemWidget*> it(m_itemToWidget);

    while(it.hasNext())
    {
        it.next();
        h += it.value()->height();
    }

    setFixedHeight(h);
}

void QOneGroupWidget::clear()
{
    qDeleteAll(m_itemToWidget.values());
    m_itemToWidget.clear();
}

void QOneGroupWidget::delItem()
{
    QStyleSheetItemWidget * wid = (QStyleSheetItemWidget*)sender();

    QMapIterator<QStyleSheetItem*,QStyleSheetItemWidget*> it(m_itemToWidget);
    while(it.hasNext())
    {
        it.next();
        if(it.value() == wid)
        {
            m_group->delItem(it.key());
            return;
        }
    }
}
