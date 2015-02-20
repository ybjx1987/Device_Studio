#include "qtimeproperty.h"

#include "../xmlnode.h"

#include <QTime>

QTimeProperty::QTimeProperty(QAbstractProperty * parent):
    QAbstractProperty(parent)
{

}

QString QTimeProperty::getValueText()
{
    QTime time = getValue().toTime();
    QString str;
    str.sprintf("%02d:%02d",time.hour(),
                time.minute());

#ifndef Q_OS_MAC
    QString s;
    s.sprintf(":%02d",time.second());
    str+=s;
#endif

    return str;
}

QIcon QTimeProperty::getValueIcon()
{
    return QIcon();
}

void QTimeProperty::makeValue(XmlNode *xml)
{
    QString h,m,s;
    h=xml->getProperty("hour");
    m=xml->getProperty("minute");
    s=xml->getProperty("second");
    QTime time;
    time.setHMS(h.toInt(),m.toInt(),s.toInt());
    m_value = QVariant::fromValue<QTime>(time);
}

void QTimeProperty::writeValue(XmlNode *xml)
{
    QTime time = getValue().toTime();
    xml->setProperty("hour",QString::number(time.hour()));
    xml->setProperty("minute",QString::number(time.minute()));
    xml->setProperty("second",QString::number(time.second()));
}
