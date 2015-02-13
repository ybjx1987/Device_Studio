#ifndef QTOOLBARBUTTON_H
#define QTOOLBARBUTTON_H

#include "platformlibglobal.h"

#include <QToolButton>

class PLATFORM_EXPORT QToolBarButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(float fader READ fader WRITE setFader)
public:
    QToolBarButton(QAction *action,QWidget *parent = 0);

    void    paintEvent(QPaintEvent *event);
    bool    event(QEvent *e);
    QSize   sizeHint() const;
    QSize   minimumSizeHint() const;


    float   fader();
    void    setFader(float value);

private slots:
    void    actionChanged();

private:
    float       m_fader;
};

#endif // QTOOLBARBUTTON_H
