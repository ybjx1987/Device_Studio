#include "qdatetimeedithost.h"

#include "../property/qdatetimeproperty.h"
#include "../property/qscriptproperty.h"

#include <QDateTimeEdit>

QDateTimeEditHost::QDateTimeEditHost(QAbstractWidgetHost * parent):
    QAbstractSpinBoxHost(parent)
{

}

void QDateTimeEditHost::createObject()
{
    m_object = new QDateTimeEdit;
    m_object->setObjectName("datetimeEdit");
    m_object->setProperty("geometry",QRect(0,0,100,20));
}

void QDateTimeEditHost::initProperty()
{
    QAbstractSpinBoxHost::initProperty();

    QAbstractProperty * pro;

    pro = new QDateTimeProperty;
    pro->setName("maximumDateTime");
    pro->setShowName(tr("MaximumDateTime"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QDateTimeProperty;
    pro->setName("minimumDateTime");
    pro->setShowName(tr("MinimumDateTime"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QDateTimeProperty;
    pro->setName("dateTime");
    pro->setShowName(tr("DateTime"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QScriptProperty;
    pro->setName("dateTimeChanged");
    pro->setShowName(tr("DateTimeChanged"));
    pro->setGroup("Attributes");
    insertProperty(pro);
}

QAbstractHostInfo * QDateTimeEditHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo;
    info->m_index = 28;
    info->m_metaObject = &(QDateTimeEditHost::staticMetaObject);
    info->m_name = "datetimeedit";
    info->m_showGroup = tr("Input Widgets");
    info->m_showIcon = ":/inner/images/widgets/datetimeedit.png";
    info->m_showName = tr("Datetime Edit");
    return info;
}

void QDateTimeEditHost::setDateTime(int year, int month, int day, int hour, int minute, int second)
{
    QDateTime dt(QDate(year,month,day),QTime(hour,minute,second));
    setPropertyValue("datetime",QVariant::fromValue<QDateTime>(dt));
}

int QDateTimeEditHost::getYear()
{
    QDateTime dt = getPropertyValue("datetime").toDateTime();
    return dt.date().year();
}

int QDateTimeEditHost::getMonth()
{
    QDateTime dt = getPropertyValue("datetime").toDateTime();
    return dt.date().month();
}

int QDateTimeEditHost::getDay()
{
    QDateTime dt = getPropertyValue("datetime").toDateTime();
    return dt.date().day();
}

int QDateTimeEditHost::getHour()
{
    QDateTime dt = getPropertyValue("datetime").toDateTime();
    return dt.time().hour();
}

int QDateTimeEditHost::getMinute()
{
    QDateTime dt = getPropertyValue("datetime").toDateTime();
    return dt.time().minute();
}

int QDateTimeEditHost::getSecond()
{
    QDateTime dt = getPropertyValue("datetime").toDateTime();
    return dt.time().second();
}

void QDateTimeEditHost::setCurrentSection(int currentSection)
{
    m_object->setProperty("currentSection",currentSection);
}

int QDateTimeEditHost::getCurrentSection()
{
    return m_object->property("currentSection").toInt();
}
