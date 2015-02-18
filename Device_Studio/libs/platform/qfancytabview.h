#ifndef QFANCYTABVIEW_H
#define QFANCYTABVIEW_H

#include "platformlibglobal.h"

#include <QWidget>
#include <QToolButton>

class QFancyTabViewWidget;

class TabViewInfo
{
public:
    QString     m_text;
    QString     m_icon;
    QString     m_uuid;
};

class PLATFORM_EXPORT QFancyTabView : public QWidget
{
    Q_OBJECT
public:
    explicit QFancyTabView(QWidget *parent = 0);
    ~QFancyTabView();

    void    addTabView(const TabViewInfo &info,int index);

    void    setTabView(const QList<TabViewInfo> &list);

    void    setCurrentIndex(int index);
protected:
    QSize minimumSizeHint()const;

    void    updateGeometry();

    bool    indexIsValid(int index);

    void    resizeEvent(QResizeEvent *);
signals:
    void    selected(int index);
public slots:
    void    widgetClicked();
    void    buttonClicked();
protected:
    QList<QFancyTabViewWidget*> m_list;

    QToolButton     *m_moreButton;

    int             m_currentIndex;

    QList<QAction*> m_buttonMenu;
};

#endif // QFANCYTABVIEW_H
