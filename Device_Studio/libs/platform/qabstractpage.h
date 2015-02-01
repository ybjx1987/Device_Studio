#ifndef QABSTRACTPAGE_H
#define QABSTRACTPAGE_H

#include "../kernel/qabstractplugin.h"

#include <QWidget>

class KERNEL_EXPORT QAbstractPage : public QAbstractPlugin
{
    Q_OBJECT
public:
    void        initPlugin();
    QString     getPluginType();
    QWidget*    getWidget();

    virtual QIcon   getPageIcon() = 0;
    virtual QString getPageText() = 0;
    virtual float   getPageIndex() = 0;
    virtual bool    getPageDefaultEnalbed() = 0;

protected:
    virtual void    createWidget() = 0;
protected:
    QWidget         *m_widget;
};

#endif // QABSTRACTPAGE_H
