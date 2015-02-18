#include "qfancytabview.h"

#include "qfancytabviewwidget.h"
#include <QHBoxLayout>
#include <QAction>
#include <QMenu>

QFancyTabView::QFancyTabView(QWidget *parent) :
    QWidget(parent),
    m_moreButton(new QToolButton),
    m_currentIndex(-1)
{
    m_moreButton->setFixedSize(22,22);
    QHBoxLayout * h = new QHBoxLayout;
    h->setMargin(0);
    h->setSpacing(0);
    h->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,
                                     QSizePolicy::Expanding));
    h->insertWidget(1,m_moreButton);
    setLayout(h);

    m_moreButton->setArrowType(Qt::DownArrow);
    connect(m_moreButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    updateGeometry();
}

QFancyTabView::~QFancyTabView()
{

}

void QFancyTabView::addTabView(const TabViewInfo &info,int index)
{
    if(index <0 || index > m_list.size())
    {
        index = m_list.size();
    }

    QFancyTabViewWidget * wid = new QFancyTabViewWidget;
    wid->setText(info.m_text);
    wid->setIcon(info.m_icon);
    m_list.insert(index,wid);

    QAction* ac = new QAction(QIcon(info.m_icon),info.m_text,this);
    ac->setProperty("uuid",info.m_uuid);
    wid->addAction(ac);

    connect(wid,SIGNAL(selected()),this,SLOT(widgetClicked()));

    updateGeometry();
}

QSize QFancyTabView::minimumSizeHint()const
{
    return QSize(0,25);
}

void QFancyTabView::updateGeometry()
{
    int w = width()-m_moreButton->width()-1;

    int count = m_list.size();

    QHBoxLayout *h = (QHBoxLayout*)layout();

    while(h->count()>2)
    {
        h->removeItem(h->itemAt(0));
    }

    QList<QFancyTabViewWidget*> list;

    QFancyTabViewWidget *currentWidget=NULL;

    if(indexIsValid(m_currentIndex))
    {
        currentWidget = m_list.at(m_currentIndex);
    }

    int allWidth = 0;
    int currentWidth = 0;

    for(int i = 0;i<count;i++)
    {
        allWidth += m_list.at(i)->width();
        if(m_currentIndex == i)
        {
            currentWidth = allWidth;
        }
    }

    list = m_list;

    if(currentWidth > w)
    {
        list.removeAll(currentWidget);
        list.insert(0,currentWidget);
    }

    m_moreButton->setVisible(allWidth>w);

    int p = 0;
    m_buttonMenu.clear();
    for(int i =0;i<count;i++)
    {
        QFancyTabViewWidget * wid = list.at(i);
        p+=wid->width();
        if(p<=w)
        {
            h->insertWidget(i,wid);
            wid->setVisible(true);
        }
        else
        {
            wid->setVisible(false);
            m_buttonMenu.append(wid->actions().first());
        }
    }
}

void QFancyTabView::setCurrentIndex(int index)
{
    if(m_currentIndex != index)
    {
        if(indexIsValid(m_currentIndex))
        {
            m_list.at(m_currentIndex)->select(false);
        }
        m_currentIndex = index;
        if(indexIsValid(m_currentIndex))
        {
            m_list.at(m_currentIndex)->select(true);
        }
        updateGeometry();
        emit selected(m_currentIndex);
    }
}

bool QFancyTabView::indexIsValid(int index)
{
    return (index>=0 && index<m_list.size());
}

void QFancyTabView::widgetClicked()
{
    QFancyTabViewWidget *wid = (QFancyTabViewWidget*)sender();
    setCurrentIndex(m_list.indexOf(wid));
}

void QFancyTabView::setTabView(const QList<TabViewInfo> &list)
{
    foreach(const TabViewInfo &info,list)
    {
        QFancyTabViewWidget * wid = new QFancyTabViewWidget;
        wid->setText(info.m_text);
        wid->setIcon(info.m_icon);
        m_list.append(wid);
        QAction* ac = new QAction(QIcon(info.m_icon),info.m_text,this);
        ac->setProperty("uuid",info.m_uuid);
        wid->addAction(ac);
        connect(wid,SIGNAL(selected()),this,SLOT(widgetClicked()));
    }

    updateGeometry();
}

void QFancyTabView::resizeEvent(QResizeEvent *)
{
    updateGeometry();
}

void QFancyTabView::buttonClicked()
{
    QMenu menu;

    menu.addActions(m_buttonMenu);

    QPoint pt=m_moreButton->pos();
    pt=this->mapToGlobal(pt+QPoint(0,24));
    if (QAction *action = menu.exec(pt))
    {
        for(int i= 0;i<m_list.size();i++)
        {
            if(action == m_list.at(i)->actions().first())
            {
                if (m_currentIndex != i)
                {
                    setCurrentIndex(i);
                }
                return;
            }
        }
    }
}
