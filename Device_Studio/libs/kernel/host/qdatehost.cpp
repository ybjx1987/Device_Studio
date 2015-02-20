#include "qdatehost.h"

#include "../property/qdateproperty.h"
#include "../property/qscriptproperty.h"

#include <QDateEdit>

QDateHost::QDateHost(QAbstractWidgetHost * parent):
    QAbstractSpinBoxHost(parent)
{

}

void QDateHost::createObject()
{
    m_object = new QDateEdit;
    m_object->setObjectName("datetime");
    m_object->setProperty("geometry",QRect(0,0,100,20));
}

void QDateHost::initProperty()
{
    QAbstractSpinBoxHost::initProperty();

    QAbstractProperty * pro;

    pro = new QDateProperty;
    pro->setName("maximumDate");
    pro->setShowName(tr("MaximumDate"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QDateProperty;
    pro->setName("minimumDate");
    pro->setShowName(tr("MinimumDate"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QDateProperty;
    pro->setName("date");
    pro->setShowName(tr("Date"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QScriptProperty;
    pro->setName("dateChanged");
    pro->setShowName(tr("DateChanged"));
    pro->setGroup("Events");
    insertProperty(pro);
}

QAbstractHostInfo* QDateHost::getHostInfo()
{
    QWidgetHostInfo *info = new QWidgetHostInfo;
    info->m_index = 27;
    info->m_metaObject = &(QDateHost::staticMetaObject);
    info->m_name = "dateedit";
    info->m_showGroup = tr("Input Widgets");
    info->m_showIcon = ":/inner/images/widgets/dateedit.png";
    info->m_showName = tr("Date Edit");

    return info;
}

void QDateHost::setDate(int year, int month, int day)
{
    QDate date(year,month,day);
    setPropertyValue("date",QVariant::fromValue<QDate>(date));
}

int QDateHost::getYear()
{
    QDate date = getPropertyValue("date").value<QDate>();
    return date.year();
}

int QDateHost::getMonth()
{
    QDate date = getPropertyValue("date").value<QDate>();
    return date.month();
}

int QDateHost::getDay()
{
    QDate date = getPropertyValue("date").value<QDate>();
    return date.day();
}

void QDateHost::setCurrentSection(int currentSection)
{
    m_object->setProperty("currentSection",currentSection);
}

int QDateHost::getCurrentSection()
{
    return m_object->property("currentSection").toInt();
}
