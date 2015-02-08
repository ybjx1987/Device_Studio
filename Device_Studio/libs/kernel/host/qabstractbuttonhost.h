#ifndef QABSTRACTBUTTONHOST_H
#define QABSTRACTBUTTONHOST_H

#include "qwidgethost.h"


class QAbstractButtonHost:public QWidgetHost
{
    Q_OBJECT
public:
    QAbstractButtonHost(QAbstractWidgetHost *parent = 0);
protected:
    void    initProperty();

public:
    void    setText(const QString &text);
    QString getText();

    void    setCheckable(bool checkable);
    bool    getCheckable();

    void    setChecked(bool checked);
    bool    getChecked();
};

#endif // QABSTRACTBUTTONHOST_H
