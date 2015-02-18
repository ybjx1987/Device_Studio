#ifndef QABSTRACTSLIDERHOST_H
#define QABSTRACTSLIDERHOST_H

#include "qwidgethost.h"

class KERNEL_EXPORT QAbstractSliderHost : public QWidgetHost
{
    Q_OBJECT
public:
    QAbstractSliderHost(QAbstractWidgetHost * parent = NULL);
protected:
    void initProperty();
public slots:
    void    setValue(int value);
    int     getValue();

    void    setSingleStep(int singleStep);
    int     getSingleStep();

    void    setOrientation(int orientation);
    int     getOrientation();

    void    setInvertedAppearance(bool invertedAppearance);
    bool    getInvertedAppearance();
};

#endif // QABSTRACTSLIDERHOST_H
