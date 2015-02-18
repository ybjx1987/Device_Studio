#include "qdateproperty.h"

#include "../xmlnode.h"

#include <QDate>

QDateProperty::QDateProperty(QAbstractProperty* parent):
    QAbstractProperty(parent)
{

}

QString QDateProperty::getValueText()
{
    QDate date = getValue().toDate();
    QString str;
    str.sprintf("%04d-%02d-%02d",date.year(),
                date.month(),date.day());
    return str;
}

QIcon QDateProperty::getValueIcon()
{
    return QIcon();
}

void QDateProperty::makeValue(XmlNode *xml)
{
    QString y,m,d;
    y=xml->getProperty("year");
    m=xml->getProperty("month");
    d=xml->getProperty("day");
    QDate date;
    date.setDate(y.toInt(),m.toInt(),d.toInt());
    m_value = QVariant::fromValue<QDate>(date);
}

void QDateProperty::writeValue(XmlNode *xml)
{
    QDate date = getValue().toDate();
    xml->setProperty("year",QString::number(date.year()));
    xml->setProperty("month",QString::number(date.month()));
    xml->setProperty("day",QString::number(date.day()));
}
