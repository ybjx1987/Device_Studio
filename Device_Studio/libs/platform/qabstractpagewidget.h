#ifndef QABSTRACTPAGEWIDGET_H
#define QABSTRACTPAGEWIDGET_H

#include "platformlibglobal.h"

#include <QWidget>

class PLATFORM_EXPORT QAbstractPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QAbstractPageWidget(QWidget *parent = 0);

    void        setVisible(bool visible);
signals:
    void        select(bool select);
public slots:
};

#endif // QABSTRACTPAGEWIDGET_H
