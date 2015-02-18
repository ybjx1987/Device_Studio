#ifndef QDATETIMEEDITHOST_H
#define QDATETIMEEDITHOST_H

#include "qabstractspinboxhost.h"

class KERNEL_EXPORT QDateTimeEditHost : public QAbstractSpinBoxHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QDateTimeEditHost(QAbstractWidgetHost * parent = NULL);

    static QAbstractHostInfo *getHostInfo();
protected:
    void    createObject();
    void    initProperty();
public slots:
    void setDateTime(int year,int month,int day,int hour,int minute,int second);
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMinute();
    int getSecond();

    void setCurrentSection(int currentSection);
    int getCurrentSection();
};

#endif // QDATETIMEEDITHOST_H
