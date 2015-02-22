#ifndef QSTRINGPROPERTYEDITOR_H
#define QSTRINGPROPERTYEDITOR_H

#include "qbuttonpropertyeditor.h"

class PLATFORM_EXPORT QStringPropertyEditor : public QButtonPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QStringPropertyEditor(QAbstractProperty * property = NULL);

    void buttonClicked();
};

#endif // QSTRINGPROPERTYEDITOR_H
