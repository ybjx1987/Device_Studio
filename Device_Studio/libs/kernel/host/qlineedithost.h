#ifndef QLINEEDITHOST_H
#define QLINEEDITHOST_H

#include "qwidgethost.h"

class KERNEL_EXPORT QLineEditHost : public QWidgetHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QLineEditHost(QAbstractWidgetHost *parent = 0);

public slots:
    void        setText(const QString &text);
    QString     getText();

    void        setAlignment(int alignment);
    int         getAlignment();

    void        setFrame(bool frame);
    bool        getFrame();

    void        setReadOnly(bool readOnly);
    bool        getReadOnly();

public:
    static QWidgetHostInfo * getHostInfo();

protected:
    void        initProperty();
    void        createObject();
};

#endif // QLINEEDITHOST_H
