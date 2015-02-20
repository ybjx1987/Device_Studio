#include "qdatetimeproperty.h"

#include "../xmlnode.h"

#include <QDateTime>

QDateTimeProperty::QDateTimeProperty(QAbstractProperty * parent):
    QAbstractProperty(parent)
{

}

QString QDateTimeProperty::getValueText()
{
    QString str;
    QDateTime dt = getValue().toDateTime();

    str.sprintf("%04d-%02d-%02d %02d:%02d",
                dt.date().year(),dt.date().month(),dt.date().day(),
                dt.time().hour(),dt.time().minute());
#ifndef Q_OS_MAC
    QString s;
    s.sprintf(":%02d",dt.time().second());
    str +=s;
#endif
    return str;
}

QIcon QDateTimeProperty::getValueIcon()
{
    return QIcon();
}

void QDateTimeProperty::makeValue(XmlNode *xml)
{
    QString year,month,day,hour,minute,second;
    year = xml->getProperty("year");
    month = xml->getProperty("month");
    day = xml->getProperty("day");
    hour = xml->getProperty("hour");
    minute = xml->getProperty("minute");
    second = xml->getProperty("second");

    QDateTime dt;
    QDate date;
    date.setDate(year.toInt(),month.toInt(),day.toInt());
    QTime time;
    time.setHMS(hour.toInt(),minute.toInt(),second.toInt());
    dt.setDate(date);
    dt.setTime(time);
    setValue(QVariant::fromValue<QDateTime>(dt));
}

void QDateTimeProperty::writeValue(XmlNode *xml)
{
    QDateTime dt = getValue().value<QDateTime>();

    xml->setProperty("year",QString::number(dt.date().year()));
    xml->setProperty("month",QString::number(dt.date().month()));
    xml->setProperty("day",QString::number(dt.date().day()));
    xml->setProperty("hour",QString::number(dt.time().hour()));
    xml->setProperty("minute",QString::number(dt.time().minute()));
    xml->setProperty("second",QString::number(dt.time().second()));
}
