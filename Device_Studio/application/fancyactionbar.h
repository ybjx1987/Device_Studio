#ifndef FANCYACTIONBAR_H
#define FANCYACTIONBAR_H

#include <QWidget>
#include <QToolButton>

class FancyToolButton : public QToolButton//做边工具条按钮
{
    Q_OBJECT
    Q_PROPERTY(float fader READ fader WRITE setFader)//透明因素

public:
    FancyToolButton(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);//绘图
    bool event(QEvent *e);//消息
    QSize sizeHint() const;//大小
    QSize minimumSizeHint() const;//最小大小


    float fader();//获取
    void setFader(float value);//设置

private slots:
    void actionChanged();

private:
    float m_fader;
};

class FancyActionBar : public QWidget
{
    Q_OBJECT
public:
    explicit FancyActionBar(QWidget *parent = 0);
    ~FancyActionBar();

signals:

public slots:
};

#endif // FANCYACTIONBAR_H
