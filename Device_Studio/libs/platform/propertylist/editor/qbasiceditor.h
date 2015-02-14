#ifndef QBASICEDITOR_H
#define QBASICEDITOR_H

#include "qabstractpropertyeditor.h"

#include <QLabel>

class PLATFORM_EXPORT QBasicEditor : public QAbstractPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QBasicEditor(QAbstractProperty* property);

signals:

public slots:
    void    propertyValueChanged();
protected:

    QLabel      *m_icon;
    QLabel      *m_text;
};

#endif // QBASICEDITOR_H
