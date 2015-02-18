#ifndef QLCDNUMBERHOST_H
#define QLCDNUMBERHOST_H

#include "qframehost.h"

class KERNEL_EXPORT QLCDNumberHost : public QFrameHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QLCDNumberHost(QAbstractWidgetHost * parent = NULL);

    static QAbstractHostInfo *getHostInfo();
public slots:
    void    setIntValue(int intValue);
    int     getIntValue();

    void    setValue(float value);
    float   getValue();

    void    setMode(int mode);
    int     getMode();

    void    setSegmentStyle(int segmentStyle);
    int     getSegmentStyle();

    void    setDigitCount(int digitCount);
    int     getDigitCount();

    void    setNumDigits(int numDigits);
    int     getNumDigits();
protected:
    void    createObject();
    void    initProperty();
};

#endif // QLCDNUMBERHOST_H
