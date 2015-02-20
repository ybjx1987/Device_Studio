#include "qlcdnumberhost.h"

#include "../property/qintproperty.h"
#include "../property/qfloatproperty.h"
#include "../property/qenumproperty.h"
#include "../property/qscriptproperty.h"
#include "../qvarianttype.h"

#include <QLCDNumber>

QLCDNumberHost::QLCDNumberHost(QAbstractWidgetHost* parent):
    QFrameHost(parent)
{
    setProperty("needFrame",false);
    setProperty("acceptDrop",false);
}

void QLCDNumberHost::createObject()
{
    m_object = new QLCDNumber;
    m_object->setObjectName("lcdnumber");
    m_object->setProperty("geometry",QRect(0,0,100,30));
}

void QLCDNumberHost::initProperty()
{
    QFrameHost::initProperty();

    QAbstractProperty * pro ;

    pro = new QIntProperty;
    pro->setName("digitCount");
    pro->setShowName(tr("Digit Count"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("numDigits");
    pro->setShowName(tr("NumDigits"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("intValue");
    pro->setShowName(tr("IntValue"));
    pro->setGroup("Attributes");
    insertProperty(pro,1);

    pro = new QFloatProperty;
    pro->setName("value");
    pro->setShowName(tr("Value"));
    pro->setGroup("Attributes");
    insertProperty(pro,2);

    pro = new QEnumProperty;
    pro->setName("mode");
    pro->setShowName(tr("Mode"));
    pro->setGroup("Attributes");
    ComboItems items;
    tagComboItem item;

    item.m_text=tr("Hex");
    item.m_value=QLCDNumber::Hex;
    items.append(item);

    item.m_text=tr("Dec");
    item.m_value=QLCDNumber::Dec;
    items.append(item);

    item.m_text=tr("Oct");
    item.m_value=QLCDNumber::Oct;
    items.append(item);

    item.m_text=tr("Bin");
    item.m_value=QLCDNumber::Bin;
    items.append(item);
    pro->setProperty("items",QVariant::fromValue<ComboItems>(items));
    insertProperty(pro);

    pro = new QEnumProperty;
    pro->setName("segmentStyle");
    pro->setShowName(tr("SegmentStyle"));
    pro->setGroup("Attributes");

    items.clear();

    item.m_text=tr("Outline");
    item.m_value=QLCDNumber::Outline;
    items.append(item);

    item.m_text=tr("Filled");
    item.m_value=QLCDNumber::Filled;
    items.append(item);

    item.m_text=tr("Flat");
    item.m_value=QLCDNumber::Flat;
    items.append(item);

    pro->setProperty("items",QVariant::fromValue<ComboItems>(items));

    insertProperty(pro);
}

QAbstractHostInfo * QLCDNumberHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo;
    info->m_index = 32;
    info->m_metaObject = &(QLCDNumberHost::staticMetaObject);
    info->m_showGroup = tr("Display Widgets");
    info->m_showName = tr("LCD Number");
    info->m_showIcon = ":/inner/images/widgets/lcdnumber.png";
    info->m_name = "lacnumber";
    return info;
}

void QLCDNumberHost::setIntValue(int intValue)
{
    setPropertyValue("intValue",intValue);
}

int QLCDNumberHost::getIntValue()
{
    return getPropertyValue("intValue").toInt();
}

void QLCDNumberHost::setValue(float value)
{
    setPropertyValue("value",value);
}

float QLCDNumberHost::getValue()
{
    return getPropertyValue("value").toFloat();
}

void QLCDNumberHost::setMode(int mode)
{
    setPropertyValue("mode",mode);
}

int QLCDNumberHost::getMode()
{
    return getPropertyValue("mode").toInt();
}

void QLCDNumberHost::setSegmentStyle(int segmentStyle)
{
    setPropertyValue("segmentStyle",segmentStyle);
}

int QLCDNumberHost::getSegmentStyle()
{
    return getPropertyValue("segmentStyle").toInt();
}

void QLCDNumberHost::setDigitCount(int digitCount)
{
    setPropertyValue("digitCount",digitCount);
}

int QLCDNumberHost::getDigitCount()
{
    return getPropertyValue("digitCount").toInt();
}

void QLCDNumberHost::setNumDigits(int numDigits)
{
    setPropertyValue("numDigits",numDigits);
}

int QLCDNumberHost::getNumDigits()
{
    return getPropertyValue("numDigits").toInt();
}
