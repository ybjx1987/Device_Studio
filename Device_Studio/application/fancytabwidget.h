#ifndef FANCYTABWIDGET_H
#define FANCYTABWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QIcon>
#include <QTimer>
#include <QSplitter>
#include <QStackedLayout>
#include <QStatusBar>

class FancyActionBar;
class QStatusWidget;

class FancyTab: public QObject
{
    Q_OBJECT
    Q_PROPERTY(float fader READ getFader WRITE setFader)
public:
    FancyTab(QWidget *tabbar);

    void        fadeIn();
    void        fadeOut();

    float       getFader();
    void        setFader(float fader);

    QIcon       getIcon();
    void        setIcon(const QIcon &icon);

    QString     getText();
    void        setText(const QString &text);

    QString     getToolTip();
    void        setToolTip(const QString &toopTip);

    bool        getEnabled();
    void        setEnabled(bool enabled);
protected:
    QPropertyAnimation  m_animator;
    QWidget             *m_tabbar;
    float               m_fader;
    QIcon               m_icon;
    QString             m_text;
    QString             m_toolTip;
    bool                m_enabled;
};

class FancyTabBar: public QWidget
{
    Q_OBJECT
public:
    FancyTabBar(QWidget *parent = NULL);
    ~FancyTabBar();
public:
    bool    event(QEvent *event);
    void    paintEvent(QPaintEvent *event);
    void    paintTab(QPainter * painter,int tabIndex) const;
    void    mousePressEvent(QMouseEvent *);
    void    mouseMoveEvent(QMouseEvent *);
    void    enterEvent(QEvent *);
    void    leaveEvent(QEvent *);

    QSize   sizeHint()const;
    QSize   minimumSizeHint()const;
public:
    bool    validIndex(int index)const ;

    int     getTabCount()const;

    QRect   getTabRect(int index) const;

    QString getTabText(int index)const;
    void    setTabText(int index,const QString & text);

    QIcon   getTabIcon(int index)const;
    void    setTabIcon(int index,const QIcon &icon);

    QString getTabToolTip(int index)const;
    void    setTabToolTip(int index,const QString &tooltip);

    void    setTabEnabled(int index,bool enabled);
    bool    getTabEnabled(int index)const;

    void    insertTab(int index,const QIcon &icon,const QString &label);

    void    setCurrentIndex(int index);
    int     getCurrentIndex();

    int     findTab(const QString &label);
private:
    QSize tabSizeHint(bool minimum = false) const;
signals:
    void currentChanged(int);
public slots:
    void emitCurrentIndex();
private:
    static const int m_rounding;
    static const int m_textPadding;
    QRect m_hoverRect;
    int m_hoverIndex;
    int m_currentIndex;
    QList<FancyTab*> m_tabs;
    QTimer m_triggerTimer;
};

class FancyTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FancyTabWidget(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
signals:

public slots:
private:
    FancyTabBar * m_tabBar;
    QStackedLayout *m_modesStack;
    QStatusBar  *m_statusbar;
    QWidget *m_selectionWidget;
    FancyActionBar      *m_actionBar;
    QStatusWidget       *m_statusWidget;
    QSplitter           *m_splitter;
};

#endif // FANCYTABWIDGET_H
