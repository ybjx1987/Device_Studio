#ifndef QBYTEARRAYEDITOR_H
#define QBYTEARRAYEDITOR_H

#include "qabstractpropertyeditor.h"

#include "../../qvalidatoredit.h"

class PLATFORM_EXPORT QByteArrayEditor : public QAbstractPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QByteArrayEditor(QAbstractProperty * property);
public slots:
    void    edit();
protected:
    QValidatorEdit       *m_lineEdit;
};

#endif // QBYTEARRAYEDITOR_H
