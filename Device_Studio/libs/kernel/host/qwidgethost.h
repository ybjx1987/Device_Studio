#ifndef QWIDGETHOST_H
#define QWIDGETHOST_H

#include "qabstractwidgethost.h"

class KERNEL_EXPORT QWidgetHostInfo: public QAbstractHostInfo
{
public:
    QWidgetHostInfo(){m_type = "Widget";}
    QString     m_showName;
    QString     m_showIcon;
    QString     m_showGroup;
    float       m_index;
};

class KERNEL_EXPORT QWidgetHost : public QAbstractWidgetHost
{
    Q_OBJECT
public:
    QWidgetHost(QAbstractWidgetHost * parent = NULL);

    static QAbstractHostInfo * getHostInfo();
protected:
    void    initProperty();
public slots:
    void    setVisible(bool visible);
    bool    getVisible();

    void    setFocus();
    void    killFocus();
protected:
    void    createObject();
};

#endif // QWIDGETHOST_H
