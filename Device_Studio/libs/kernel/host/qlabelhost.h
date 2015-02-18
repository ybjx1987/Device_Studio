#ifndef QLABELHOST_H
#define QLABELHOST_H

#include "qframehost.h"

class KERNEL_EXPORT QLabelHost : public QFrameHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QLabelHost(QAbstractWidgetHost * parent = NULL);

    static QAbstractHostInfo * getHostInfo();
public slots:
    void    setText(const QString &text);
    QString getText();

    void    setWordWrap(bool wordWrap);
    bool    getWordWrap();

    void    setAlignment(int alignment);
    int     getAlignment();
protected:
    void    createObject();
    void    initProperty();
};

#endif // QLABELHOST_H
