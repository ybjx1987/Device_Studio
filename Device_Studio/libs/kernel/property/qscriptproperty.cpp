#include "qscriptproperty.h"

QScriptProperty::QScriptProperty(QAbstractProperty * parent):
    QAbstractProperty(parent)
{

}

QString QScriptProperty::getValueText()
{
    QString str=getValue().toString();
    str.replace("\r\n"," ");
    str.replace("\n"," ");
    return str;
}

QIcon QScriptProperty::getValueIcon()
{
    return QIcon();
}
