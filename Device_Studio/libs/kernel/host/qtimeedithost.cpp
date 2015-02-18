#include "qtimeedithost.h"

#include "../property/qscriptproperty.h"
#include "../property/qtimeproperty.h"

#include <QTimeEdit>

QTimeEditHost::QTimeEditHost(QAbstractWidgetHost * parent):
    QAbstractSpinBoxHost(parent)
{

}

QAbstractHostInfo * QTimeEditHost::getHostInfo()
{
    QWidgetHostInfo *info = new QWidgetHostInfo;
    info->m_index = 26;
    info->m_name = "timeedit";
    info->m_metaObject =&(QTimeEditHost::staticMetaObject);
    info->m_showGroup = tr("Input Widgets");
    info->m_showName = tr("Time Edit");
    info->m_showIcon = ":/inner/images/widgets/timeedit.png";
    return info;
}

void QTimeEditHost::createObject()
{
    m_object = new QTimeEdit;
    m_object->setObjectName("timeEdit");
    m_object->setProperty("geometry",QRect(0,0,100,20));
}

void QTimeEditHost::initProperty()
{
    QAbstractSpinBoxHost::initProperty();

    QAbstractProperty * pro;

    pro = new QTimeProperty;
    pro->setName("maximumTime");
    pro->setShowName(tr("MaximumTime"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QTimeProperty;
    pro->setName("minimumTime");
    pro->setShowName(tr("MinimumTime"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QTimeProperty;
    pro->setName("time");
    pro->setShowName(tr("Time"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QScriptProperty;
    pro->setName("timeChanged");
    pro->setShowName(tr("Time Changed"));
    pro->setGroup("Attributes");
    insertProperty(pro);
}

void QTimeEditHost::setTime(int hour, int minute, int second)
{
    QTime time(hour,minute,second);
    setPropertyValue("time",QVariant::fromValue<QTime>(time));
}

int QTimeEditHost::getHour()
{
    QTime time = getPropertyValue("time").toTime();
    return time.hour();
}

int QTimeEditHost::getMinute()
{
    QTime time = getPropertyValue("time").toTime();
    return time.minute();
}

int QTimeEditHost::getSecond()
{
    QTime time = getPropertyValue("time").toTime();
    return time.second();
}

void QTimeEditHost::setCurrentSection(int currentSection)
{
    m_object->setProperty("currentSection",currentSection);
}

int QTimeEditHost::getCurrentSection()
{
    return m_object->property("currentSection").toInt();
}
