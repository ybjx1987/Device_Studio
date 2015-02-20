#ifndef QTIMEEDITHOST_H
#define QTIMEEDITHOST_H

#include "qabstractspinboxhost.h"

class KERNEL_EXPORT QTimeEditHost : public QAbstractSpinBoxHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QTimeEditHost(QAbstractWidgetHost * parent=NULL);

    static QAbstractHostInfo * getHostInfo();
protected:
    void    createObject();
    void    initProperty();
public slots:
    void    setTime(int hour,int minute,int second);
    int     getHour();
    int     getMinute();
    int     getSecond();

    void    setCurrentSection(int currentSection);
    int     getCurrentSection();
};

#endif // QTIMEEDITHOST_H
