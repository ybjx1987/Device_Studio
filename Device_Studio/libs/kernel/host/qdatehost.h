#ifndef QDATEHOST_H
#define QDATEHOST_H

#include "qabstractspinboxhost.h"

class KERNEL_EXPORT QDateHost : public QAbstractSpinBoxHost
{
    Q_OBJECT
public:
    Q_INVOKABLE QDateHost(QAbstractWidgetHost * parent = NULL);

    static QAbstractHostInfo *getHostInfo();

protected:
    void    createObject();
    void    initProperty();

public slots:
    void    setDate(int year,int month,int day);
    int     getYear();
    int     getMonth();
    int     getDay();

    void    setCurrentSection(int currentSection);
    int     getCurrentSection();
};

#endif // QDATEHOST_H
