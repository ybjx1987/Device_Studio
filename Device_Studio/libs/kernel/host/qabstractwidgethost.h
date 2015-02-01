#ifndef QABSTRACTWIDGETHOST_H
#define QABSTRACTWIDGETHOST_H

#include "qabstracthost.h"

class KERNEL_EXPORT QAbstractWidgetHost : public QAbstractHost
{
    Q_OBJECT
public:
    QAbstractWidgetHost(QAbstractWidgetHost * parent = NULL);

protected:
    void    initProperty();
public slots:
    void    setGeometry(int x,int y,int width,int height);
    int     getX();
    int     getY();
    int     getWidth();
    int     getHeight();

    void    setEnabled(bool enabled);
    bool    getEnabled();

    void    setToolTip(const QString &tooltip);
    QString getToolTip();

    void    setCursor(int cursor);
    int     getCursor();

    void    setLevel(int level);
    int     getLevel();
};

#endif // QABSTRACTWIDGETHOST_H
