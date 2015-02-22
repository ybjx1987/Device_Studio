#ifndef QBUTTONPROPERTYEDITOR_H
#define QBUTTONPROPERTYEDITOR_H

#include "qbasiceditor.h"

class QButtonPropertyEditor : public QBasicEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QButtonPropertyEditor(QAbstractProperty* property);
protected:
    void    mouseDoubleClickEvent(QMouseEvent *);
public slots:
    virtual void    buttonClicked();
};

#endif // QBUTTONPROPERTYEDITOR_H
