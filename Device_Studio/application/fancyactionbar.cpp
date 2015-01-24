#include "fancyactionbar.h"

#include "../libs/platform/stylehelper.h"

#include <QPropertyAnimation>
#include <QPainter>
#include <QEvent>
#include <QAction>

/**
 * @brief 构造函数
 * @param parent--父窗口
 */
FancyToolButton::FancyToolButton(QWidget *parent)
    : QToolButton(parent),
      m_fader(0)
{
    setAttribute(Qt::WA_Hover, true);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

/**
 * @brief 获取透明度系数
 * @return 透明度系数
 */
float FancyToolButton::fader()
{
    return m_fader;
}

/**
 * @brief 设置透明度系数
 * @param value--透明度系数
 */
void FancyToolButton::setFader(float value)
{
    m_fader=value;
    update();
}

/**
 * @brief 绘图函数
 * @param event--绘图事件指针
 */
void FancyToolButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    if (m_fader > 0 && isEnabled() && !isDown() && !isChecked())
    {//绘制动画过程
        painter.save();
        int fader = int(40 * m_fader);
        QLinearGradient grad(rect().topLeft(), rect().topRight());
        grad.setColorAt(0, Qt::transparent);
        grad.setColorAt(0.5, QColor(255, 255, 255, fader));
        grad.setColorAt(1, Qt::transparent);
        painter.fillRect(rect(), grad);
        painter.setPen(QPen(grad, 1.0));
        painter.drawLine(rect().topLeft(), rect().topRight());
        painter.drawLine(rect().bottomLeft(), rect().bottomRight());
        painter.restore();
    }
    else if (isDown() || isChecked())
    {//绘制按下或选中状态
        painter.save();
        QLinearGradient grad(rect().topLeft(), rect().topRight());
        grad.setColorAt(0, Qt::transparent);
        grad.setColorAt(0.5, QColor(0, 0, 0, 50));
        grad.setColorAt(1, Qt::transparent);
        painter.fillRect(rect(), grad);
        painter.setPen(QPen(grad, 1.0));
        painter.drawLine(rect().topLeft(), rect().topRight());
        painter.drawLine(rect().topLeft(), rect().topRight());
        painter.drawLine(rect().topLeft() + QPoint(0,1), rect().topRight() + QPoint(0,1));
        painter.drawLine(rect().bottomLeft(), rect().bottomRight());
        painter.drawLine(rect().bottomLeft(), rect().bottomRight());
        painter.drawLine(rect().topLeft() - QPoint(0,1), rect().topRight() - QPoint(0,1));
        painter.restore();
    }

    QRect iconRect(0, 0,32,32);//绘制图标
    iconRect.moveCenter(rect().center());
    StyleHelper::drawIconWithShadow(icon(), iconRect, &painter, isEnabled() ? QIcon::Normal : QIcon::Disabled);
}

/**
 * @brief 事件处理函数
 * @param e--事件指针
 * @return 返回值不重要
 */
bool FancyToolButton::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::Enter:
        {//鼠标进入
            QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
            animation->setDuration(125);
            animation->setEndValue(1.0);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        break;
    case QEvent::Leave:
        {//鼠标离开
            QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
            animation->setDuration(125);
            animation->setEndValue(0.0);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        break;
    default:
        return QToolButton::event(e);
    }
    return false;
}

/**
 * @brief 控制按钮大小
 * @return 返回按钮的大小
 */
QSize FancyToolButton::sizeHint() const
{
    QSizeF buttonSize = iconSize().expandedTo(QSize(64, 38));
    return buttonSize.toSize();
}

/**
 * @brief 控制按钮的最小大小
 * @return 按钮的最小大小
 */
QSize FancyToolButton::minimumSizeHint() const
{
    return QSize(8, 8);
}

/**
 * @brief 状态改变的槽函数
 */
void FancyToolButton::actionChanged()
{
    if (QAction* action = defaultAction())
        setVisible(action->isVisible());
}


/**
 * @brief 构造函数
 * @param parent--父窗口
 */
FancyActionBar::FancyActionBar(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("actionbar");
    m_actionsLayout = new QVBoxLayout();
    QVBoxLayout *spacerLayout = new QVBoxLayout();
    spacerLayout->addLayout(m_actionsLayout);
    int sbh = 8;
    spacerLayout->addSpacing(sbh);
    spacerLayout->setMargin(0);
    spacerLayout->setSpacing(0);
    setLayout(spacerLayout);
    setContentsMargins(0,2,0,0);
}

/**
 * @brief 重绘函数
 */
void FancyActionBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QColor light = StyleHelper::sidebarHighlight();
    QColor dark = StyleHelper::sidebarShadow();
    painter.setPen(dark);
    painter.drawLine(rect().topLeft(),rect().topRight());
    painter.setPen(light);
    painter.drawLine(rect().topLeft()+QPoint(1,1),
                     rect().topRight()+QPoint(0,1));
}

/**
 * @brief 添加新的按钮
 * @param action--按钮的action
 */
void FancyActionBar::addProjectSelector(QAction *action)
{
    FancyToolButton * toolButton = new FancyToolButton(this);
    toolButton->setDefaultAction(action);
    connect(action,SIGNAL(changed()),toolButton,SLOT(actionChanged()));
    m_actionsLayout->insertWidget(-1,toolButton);
    m_buttons.insert(action,toolButton);
}

/**
 * @brief 设置按钮的可见性
 * @param action--按钮的action
 * @param visible--可见性
 */
void FancyActionBar::setButtonVisible(QAction *action, bool visible)
{
    FancyToolButton *button = m_buttons.value(action);
    if(button != NULL)
    {
        button->setVisible(visible);
    }
}

/**
 * @brief 获取工具条的布局
 * @return 工具条的布局
 */
QLayout * FancyActionBar::actionsLayout() const
{
    return m_actionsLayout;
}
