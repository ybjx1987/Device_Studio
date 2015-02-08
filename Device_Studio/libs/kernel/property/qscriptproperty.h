#ifndef QSCRIPTPROPERTY_H
#define QSCRIPTPROPERTY_H

#include "qabstractproperty.h"

class QScriptProperty : public QAbstractProperty
{
    Q_OBJECT
public:
    QScriptProperty(QAbstractProperty * parent = NULL);


    QString         getValueText();
    QIcon           getValueIcon();
};

#endif // QSCRIPTPROPERTY_H
