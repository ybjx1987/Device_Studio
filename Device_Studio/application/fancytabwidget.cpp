#include "fancytabwidget.h"

#include "qstatuswidget.h"
#include "fancyactionbar.h"

#include "../libs/platform/stylehelper.h"
#include "../libs/platform/styledbar.h"
#include "../libs/platform/minisplitter.h"

#include <QStyleFactory>
#include <QHelpEvent>
#include <QToolTip>
#include <QPainter>
#include <QStyle>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QColorDialog>

const int FancyTabBar::m_rounding = 22;
const int FancyTabBar::m_textPadding = 4;

FancyTab::FancyTab(QWidget *tabbar):
    QObject(NULL),
    m_tabbar(tabbar),
    m_fader(0),
    m_enabled(true)
{
    m_animator.setPropertyName("fader");
    m_animator.setTargetObject(this);
}

void FancyTab::fadeIn()
{
    m_animator.stop();
    m_animator.setDuration(80);
    m_animator.setEndValue(40);
    m_animator.start();
}

void FancyTab::fadeOut()
{
    m_animator.stop();
    m_animator.setDuration(160);
    m_animator.setEndValue(0);
    m_animator.start();
}

float FancyTab::getFader()
{
    return m_fader;
}

void FancyTab::setFader(float fader)
{
    m_fader = fader;
    m_tabbar->update();
}

QIcon FancyTab::getIcon()
{
    return m_icon;
}

void FancyTab::setIcon(const QIcon &icon)
{
    m_icon = icon;
}

QString FancyTab::getText()
{
    return m_text;
}

void FancyTab::setText(const QString &text)
{
    m_text = text;
}

QString FancyTab::getToolTip()
{
    return m_toolTip;
}

void FancyTab::setToolTip(const QString &toolTip)
{
    m_toolTip = toolTip;
}

bool FancyTab::getEnabled()
{
    return m_enabled;
}

void FancyTab::setEnabled(bool enabled)
{
    m_enabled = enabled;
}


FancyTabBar::FancyTabBar(QWidget *parent):
    QWidget(parent)
{
    m_hoverIndex = -1;
    m_currentIndex = -1;
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    setStyle(QStyleFactory::create("windows"));
    setMinimumWidth(qMax(2*m_rounding,40));
    setAttribute(Qt::WA_Hover,true);
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(true);
    m_triggerTimer.setSingleShot(true);
    connect(&m_triggerTimer,SIGNAL(timeout()),this,SLOT(emitCurrentIndex()));
}

FancyTabBar::~FancyTabBar()
{
    qDeleteAll(m_tabs);
    delete style();
}

QSize FancyTabBar::tabSizeHint(bool minimum) const
{
    QFont boldFont(font());
    boldFont.setPointSizeF(StyleHelper::sidebarFontSize());
    boldFont.setBold(true);
    QFontMetrics fm(boldFont);
    int spacing = 8;
    int width = 60 + spacing + 2;
    int maxLabelwidth = 0;
    for (int tab=0 ; tab<getTabCount() ;++tab) {
        int width = fm.width(getTabText(tab));
        if (width > maxLabelwidth)
            maxLabelwidth = width;
    }
    int iconHeight = minimum ? 0 : 32;
    return QSize(qMax(width, maxLabelwidth + 4), iconHeight + spacing + fm.height());

}

void FancyTabBar::emitCurrentIndex()
{
    emit currentChanged(m_currentIndex);
}

bool FancyTabBar::event(QEvent *event)
{
    if(event->type() == QEvent::ToolTip)
    {
        if(validIndex(m_hoverIndex))
        {
            if(!getTabToolTip(m_hoverIndex).isEmpty())
            {
                QToolTip::showText(static_cast<QHelpEvent*>(event)->globalPos(),
                                   getTabToolTip(m_hoverIndex),this);
                return true;
            }
        }
    }
    return QWidget::event(event);
}

void FancyTabBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    for(int i=0;i<getTabCount();i++)
    {
        if(i != m_currentIndex)
        {
            paintTab(&p,i);
        }
    }
    if(m_currentIndex != -1)
    {
        paintTab(&p,m_currentIndex);
    }

}

void FancyTabBar::paintTab(QPainter *painter, int tabIndex) const
{
    if (!validIndex(tabIndex)) {
        qWarning("invalid index");
        return;
    }
    painter->save();

    QRect rect = getTabRect(tabIndex);
    bool selected = (tabIndex == m_currentIndex);
    bool enabled = getTabEnabled(tabIndex);

    if (selected) {
        painter->save();
        QLinearGradient grad(rect.topLeft(), rect.topRight());
        grad.setColorAt(0, QColor(255, 255, 255, 140));
        grad.setColorAt(1, QColor(255, 255, 255, 210));
        painter->fillRect(rect.adjusted(0, 0, 0, -1), grad);
        painter->restore();

        painter->setPen(QColor(0, 0, 0, 110));
        painter->drawLine(rect.topLeft() + QPoint(1,-1), rect.topRight() - QPoint(0,1));
        painter->drawLine(rect.bottomLeft(), rect.bottomRight());
        painter->setPen(QColor(0, 0, 0, 40));
        painter->drawLine(rect.topLeft(), rect.bottomLeft());

        painter->setPen(QColor(255, 255, 255, 50));
        painter->drawLine(rect.topLeft() + QPoint(0, -2), rect.topRight() - QPoint(0,2));
        painter->drawLine(rect.bottomLeft() + QPoint(0, 1), rect.bottomRight() + QPoint(0,1));
        painter->setPen(QColor(255, 255, 255, 40));
        painter->drawLine(rect.topLeft() + QPoint(0, 0), rect.topRight());
        painter->drawLine(rect.topRight() + QPoint(0, 1), rect.bottomRight() - QPoint(0, 1));
        painter->drawLine(rect.bottomLeft() + QPoint(0,-1), rect.bottomRight()-QPoint(0,1));
    }

    QString tabText=getTabText(tabIndex);
    QRect tabTextRect(rect);
    const bool drawIcon = rect.height() > 36;
    QRect tabIconRect(tabTextRect);
    tabTextRect.translate(0, drawIcon ? -2 : 1);
    QFont boldFont(painter->font());
    boldFont.setPointSizeF(StyleHelper::sidebarFontSize());
    boldFont.setBold(true);
    painter->setFont(boldFont);
    painter->setPen(selected ? QColor(255, 255, 255, 160) : QColor(0, 0, 0, 110));
    const int textFlags = Qt::AlignCenter | (drawIcon ? Qt::AlignBottom : Qt::AlignVCenter) | Qt::TextWordWrap;
    if (enabled) {
        painter->drawText(tabTextRect, textFlags, tabText);
        painter->setPen(selected ? QColor(60, 60, 60) : StyleHelper::panelTextColor());
    } else {
        painter->setPen(selected ? StyleHelper::panelTextColor() : QColor(0, 0, 0, 120));
    }
    if (!selected && enabled) {
        painter->save();
        int fader = int(m_tabs[tabIndex]->getFader());
        QLinearGradient grad(rect.topLeft(), rect.topRight());
        grad.setColorAt(0, Qt::transparent);
        grad.setColorAt(0.5, QColor(255, 255, 255, fader));
        grad.setColorAt(1, Qt::transparent);
        painter->fillRect(rect, grad);
        painter->setPen(QPen(grad, 1.0));
        painter->drawLine(rect.topLeft(), rect.topRight());
        painter->drawLine(rect.bottomLeft(), rect.bottomRight());
        painter->restore();
    }

    if (!enabled)
        painter->setOpacity(0.7);

    if (drawIcon) {
        int textHeight = painter->fontMetrics().boundingRect(QRect(0, 0, width(), height()), Qt::TextWordWrap, tabText).height();
        tabIconRect.adjust(0, 4, 0, -textHeight);
        StyleHelper::drawIconWithShadow(getTabIcon(tabIndex), tabIconRect, painter, enabled ? QIcon::Normal : QIcon::Disabled);
    }

    painter->translate(0, -1);
    painter->drawText(tabTextRect, textFlags, tabText);
    painter->restore();
}

void FancyTabBar::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    for(int index = 0 ; index < getTabCount();index++)
    {
        if(getTabRect(index).contains(e->pos()))
        {
            if(getTabEnabled(index))
            {
                m_currentIndex = index;
                update();
                m_triggerTimer.start(0);
            }
            break;
        }
    }
}

void FancyTabBar::mouseMoveEvent(QMouseEvent *e)
{
    int newHover = -1;
    for(int i=0 ; i<getTabCount();i++)
    {
        if(getTabRect(i).contains(e->pos()))
        {
            newHover = i;
            break;
        }
    }
    if(newHover == m_hoverIndex)
    {
        return;
    }
    if(validIndex(m_hoverIndex))
    {
        m_tabs[m_hoverIndex]->fadeOut();
    }
    m_hoverIndex = newHover;
    if(validIndex(m_hoverIndex))
    {
        m_tabs[m_hoverIndex]->fadeIn();
    }
    m_hoverRect = getTabRect(m_hoverIndex);
}

void FancyTabBar::enterEvent(QEvent *)
{
    m_hoverIndex = -1;
    m_hoverRect = QRect();
}

void FancyTabBar::leaveEvent(QEvent *)
{
    if(validIndex(m_hoverIndex))
    {
        m_tabs[m_hoverIndex]->fadeOut();
    }
    m_hoverIndex = -1;
    m_hoverRect = QRect();
}

QSize FancyTabBar::sizeHint()const
{
    QSize sh = tabSizeHint();
    return QSize(sh.width(),sh.height()*m_tabs.count());
}

QSize FancyTabBar::minimumSizeHint()const
{
    QSize sh = tabSizeHint(true);
    return QSize(sh.width(),sh.height()*m_tabs.count());
}

int FancyTabBar::getTabCount() const
{
    return m_tabs.count();
}

QRect FancyTabBar::getTabRect(int index) const
{
    if(validIndex(index))
    {
        QSize sh = tabSizeHint();

        if (sh.height() * m_tabs.count() > height())
        {
            sh.setHeight(height() / m_tabs.count());
        }
        return QRect(0, index * sh.height(), sh.width(), sh.height());
    }
    else
    {
        return QRect(0,0,0,0);
    }
}

QString FancyTabBar::getTabText(int index)const
{
    if(validIndex(index))
    {
        return m_tabs[index]->getText();
    }
    else
    {
        return "";
    }
}

void FancyTabBar::setTabText(int index, const QString &text)
{
    if(validIndex(index))
    {
        m_tabs[index]->setText(text);
    }
}

QIcon FancyTabBar::getTabIcon(int index)const
{
    if(validIndex(index))
    {
        return m_tabs[index]->getIcon();
    }
    else
    {
        return QIcon();
    }
}

void FancyTabBar::setTabIcon(int index, const QIcon &icon)
{
    if(validIndex(index))
    {
        m_tabs[index]->setIcon(icon);
    }
}

void FancyTabBar::setTabToolTip(int index, const QString &toolTip)
{
    if(validIndex(index))
    {
        m_tabs[index]->setToolTip(toolTip);
    }
}

QString FancyTabBar::getTabToolTip(int index) const
{
    if(validIndex(index))
    {
        return m_tabs[index]->getToolTip();
    }
    else
    {
        return "";
    }
}

void FancyTabBar::setTabEnabled(int index, bool enabled)
{
    if(validIndex(index))
    {
        m_tabs[index]->setEnabled(enabled);
    }
}

bool FancyTabBar::getTabEnabled(int index) const
{
    if(validIndex(index))
    {
        return m_tabs[index]->getEnabled();
    }
    else
    {
        return false;
    }
}

bool FancyTabBar::validIndex(int index) const
{
    return index >=0 && index<m_tabs.size();
}

void FancyTabBar::insertTab(int index, const QIcon &icon, const QString &label)
{
    FancyTab *tab = new FancyTab(this);
    tab->setIcon(icon);
    tab->setText(label);
    m_tabs.insert(index,tab);
}

void FancyTabBar::setCurrentIndex(int index)
{
    if(getTabEnabled(index) && m_currentIndex != index)
    {
        m_currentIndex = index;
        update();
        emit currentChanged(m_currentIndex);
    }
}

int FancyTabBar::getCurrentIndex()
{
    return m_currentIndex;
}

int FancyTabBar::findTab(const QString &label)
{
    for(int i=0;i<getTabCount();i++)
    {
        if(m_tabs[i]->getText() == label)
        {
            return i;
        }
    }
    return -1;
}

class FancyColorButton : public QWidget
{
public:
    FancyColorButton(QWidget *parent)
      : m_parent(parent)
    {
        setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    }

    void mousePressEvent(QMouseEvent *ev)
    {
        if (ev->modifiers() & Qt::ShiftModifier) {
            QColor color = QColorDialog::getColor(StyleHelper::baseColor(), m_parent);
            if (color.isValid())
                StyleHelper::setBaseColor(color);
        }
    }
private:
    QWidget *m_parent;
};

FancyTabWidget::FancyTabWidget(QWidget *parent) : QWidget(parent)
{
    m_tabBar = new FancyTabBar(this);
    m_selectionWidget = new QWidget(this);

    QVBoxLayout *selectionLayout = new QVBoxLayout;
    selectionLayout->setSpacing(0);
    selectionLayout->setMargin(0);

    StyledBar *bar = new StyledBar;
    QHBoxLayout *layout = new QHBoxLayout(bar);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(new FancyColorButton(this));
    selectionLayout->addWidget(bar);

    selectionLayout->addWidget(m_tabBar);

    m_actionBar = new FancyActionBar(this);
    selectionLayout->addWidget(m_actionBar);

    m_selectionWidget->setLayout(selectionLayout);
    m_selectionWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    m_modesStack = new QStackedLayout;
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    m_statusbar=new QStatusBar(this);
    m_statusbar->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    m_statusbar->setSizeGripEnabled(false);
    m_statusWidget=new QStatusWidget;
    m_statusbar->insertWidget(0,m_statusWidget,1);

    m_splitter = new MiniSplitter(Qt::Vertical);
    QWidget * wid = new QWidget;
    wid->setLayout(m_modesStack);
    m_splitter->addWidget(wid);
    m_splitter->setStretchFactor(0,1);
    vlayout->addWidget(m_splitter);
    vlayout->addWidget(m_statusbar);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(1);
    mainLayout->addWidget(m_selectionWidget);
    mainLayout->addLayout(vlayout);
    setLayout(mainLayout);
}

void FancyTabWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRect rect = m_selectionWidget->rect().adjusted(0, 0, 1, 0);
    rect = style()->visualRect(layoutDirection(), geometry(), rect);
    StyleHelper::verticalGradient(&painter, rect, rect);
    painter.setPen(StyleHelper::borderColor());
    painter.drawLine(rect.topRight(), rect.bottomRight());

    QColor light = StyleHelper::sidebarHighlight();
    painter.setPen(light);
    painter.drawLine(rect.bottomLeft(), rect.bottomRight());
}

void FancyTabWidget::insertTab(int index, QWidget *tab, const QIcon &icon, const QString &label)
{
    m_modesStack->insertWidget(index,tab);
    m_tabBar->insertTab(index,icon,label);
}

void FancyTabWidget::setCurrentIndex(const QString &label)
{
    int index = findTab(label);
    if(index >0 )
    {
        setCurrentIndex(index);
    }
}

void FancyTabWidget::setCurrentIndex(int index)
{
    if(m_tabBar->getTabEnabled(index))
    {
        m_tabBar->setCurrentIndex(index);
    }
}

int FancyTabWidget::findTab(const QString &name)
{
    return m_tabBar->findTab(name);
}

void FancyTabWidget::setTabEnabled(int index, bool enabled)
{
    if(index == m_tabBar->getCurrentIndex())
    {
        m_tabBar->setCurrentIndex(0);
    }
    m_tabBar->setTabEnabled(index,enabled);
}
