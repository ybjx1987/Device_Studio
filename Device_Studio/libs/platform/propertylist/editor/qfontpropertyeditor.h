#ifndef QFONTPROPERTYEDITOR_H
#define QFONTPROPERTYEDITOR_H

#include "qbuttonpropertyeditor.h"

class QFontPropertyEditor : public QButtonPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QFontPropertyEditor(QAbstractProperty *property);
protected:
    void buttonClicked();
};

#endif // QFONTPROPERTYEDITOR_H
