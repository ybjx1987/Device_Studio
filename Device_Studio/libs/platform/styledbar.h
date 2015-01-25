#ifndef STYLEDBAR_H
#define STYLEDBAR_H

#include "platformlibglobal.h"

#include <QWidget>

class PLATFORM_EXPORT StyledBar : public QWidget
{
    Q_OBJECT
public:
    explicit StyledBar(QWidget *parent = 0);
    ~StyledBar();
protected:
    void paintEvent(QPaintEvent *);
};

#endif // STYLEDBAR_H
