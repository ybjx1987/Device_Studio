#include "qabstractsliderhost.h"

#include "../property/qintproperty.h"
#include "../property/qenumproperty.h"
#include "../qvarianttype.h"
#include "../property/qboolproperty.h"
#include "../property/qscriptproperty.h"

#include <QVariant>

QAbstractSliderHost::QAbstractSliderHost(QAbstractWidgetHost * parent):
    QWidgetHost(parent)
{
    setProperty("needFrame",false);
    setProperty("acceptDrop",false);
}

void QAbstractSliderHost::initProperty()
{
    QWidgetHost::initProperty();

    QAbstractProperty * pro;
    pro = new QIntProperty;
    pro->setName("value");
    pro->setShowName(tr("value"));
    pro->setGroup("Attributes");
    insertProperty(pro,1);

    pro = new QIntProperty;
    pro->setName("minimum");
    pro->setShowName(tr("Minimum"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("maximum");
    pro->setShowName(tr("Maximum"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("singleStep");
    pro->setShowName(tr("Single Step"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QEnumProperty;
    pro->setName("orientation");
    pro->setShowName(tr("Orientation"));
    pro->setGroup("Attributes");
    ComboItems items;
    tagComboItem item;

    item.m_text=tr("Horizontal");
    item.m_value=Qt::Horizontal;
    items.append(item);

    item.m_text=tr("Vertical");
    item.m_value=Qt::Vertical;
    items.append(item);

    pro->setProperty("items",QVariant::fromValue<ComboItems>(items));
    insertProperty(pro);

    pro = new QBoolProperty;
    pro->setName("invertedAppearance");
    pro->setShowName(tr("Inverted Appearance"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QScriptProperty;
    pro->setName("valueChanged");
    pro->setShowName(tr("Value Changed"));
    pro->setGroup("Attributes");
    insertProperty(pro);
}

void QAbstractSliderHost::setValue(int value)
{
    setPropertyValue("value",value);
}

int QAbstractSliderHost::getValue()
{
    return getPropertyValue("value").toInt();
}

void QAbstractSliderHost::setSingleStep(int singleStep)
{
    setPropertyValue("singleStep",singleStep);
}

int QAbstractSliderHost::getSingleStep()
{
    return getPropertyValue("singleStep").toInt();
}

void QAbstractSliderHost::setOrientation(int orientation)
{
    setPropertyValue("orientation",orientation);
}

int QAbstractSliderHost::getOrientation()
{
    return getPropertyValue("orientation").toInt();
}

void QAbstractSliderHost::setInvertedAppearance(bool invertedAppearance)
{
    setPropertyValue("invertedAppearance",invertedAppearance);
}

bool QAbstractSliderHost::getInvertedAppearance()
{
    return getPropertyValue("invertedAppearance").toBool();
}
