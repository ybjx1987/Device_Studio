#ifndef FANCYACTIONBAR_H
#define FANCYACTIONBAR_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QMap>

/**
 * @brief 这个类定义了工具条上的按钮
 */
class FancyToolButton : public QToolButton//做边工具条按钮
{
    Q_OBJECT
    //透明度属性
    Q_PROPERTY(float fader READ fader WRITE setFader)
public:
    //构造函数
    FancyToolButton(QWidget *parent = 0);
    //重写绘图函数
    void paintEvent(QPaintEvent *event);
    //处理一些消息
    bool event(QEvent *e);
    //控制按钮大小
    QSize sizeHint() const;
    //控制按钮的最小大小
    QSize minimumSizeHint() const;
    //获取透明度系数
    float fader();
    //设置透明度系数
    void setFader(float value);
private slots:
    //状态改变的槽函数
    void actionChanged();
private:
    //透明度系数
    float m_fader;
};

/**
 * @brief 工具条类
 */
class FancyActionBar : public QWidget
{
    Q_OBJECT
public:
    //构造函数
    FancyActionBar(QWidget *parent = 0);
    //重绘函数
    void paintEvent(QPaintEvent *);
    //添加新的按钮
    void addProjectSelector(QAction *action);
    //设置按钮的可见性
    void setButtonVisible(QAction* action,bool visible);
    //获取工具条的布局指针
    QLayout *actionsLayout() const;
private:
    //工具条的布局
    QVBoxLayout *m_actionsLayout;
    //按钮集合
    QMap<QAction*,FancyToolButton*> m_buttons;
};

#endif // FANCYACTIONBAR_H
