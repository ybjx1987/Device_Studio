#ifndef QACTIONTOOLBAR_H
#define QACTIONTOOLBAR_H

#include "platformlibglobal.h"

#include <QWidget>
#include <QSpacerItem>

class QToolBarButton;

class PLATFORM_EXPORT QActionToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit QActionToolBar(QWidget *parent = 0);

    void    addButtonActions(const QList<QAction*>    &actions,
                             Qt::AlignmentFlag flag = Qt::AlignLeft);

protected:
    QList<QToolBarButton*>      m_buttons;
    QSpacerItem*                m_spacer;
};

#endif // QACTIONTOOLBAR_H
