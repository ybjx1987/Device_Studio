#include "qdoublespinboxhost.h"

#include "../property/qfloatproperty.h"
#include "../property/qintproperty.h"
#include "../property/qscriptproperty.h"

#include <QDoubleSpinBox>

QDoubleSpinBoxHost::QDoubleSpinBoxHost(QAbstractWidgetHost *parent):
    QAbstractSpinBoxHost(parent)
{

}

void QDoubleSpinBoxHost::createObject()
{
    m_object = new QDoubleSpinBox;
    m_object->setObjectName("doubleSpinbox");
    m_object->setProperty("geometry",QRect(0,0,100,20));
}

void QDoubleSpinBoxHost::initProperty()
{
    QAbstractSpinBoxHost::initProperty();

    QAbstractProperty * pro;

    pro = new QFloatProperty;
    pro->setName("maximum");
    pro->setShowName(tr("Maximum"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QFloatProperty;
    pro->setName("minimum");
    pro->setShowName(tr("Minimum"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QFloatProperty;
    pro->setName("value");
    pro->setShowName(tr("Value"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QFloatProperty;
    pro->setName("singleStep");
    pro->setShowName(tr("SingleStep"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("decimals");
    pro->setShowName(tr("Decimals"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QScriptProperty;
    pro->setName("valueChanged");
    pro->setShowName(tr("Value Changed"));
    pro->setGroup("Events");
    insertProperty(pro);
}

QAbstractHostInfo * QDoubleSpinBoxHost::getHostInfo()
{
    QWidgetHostInfo *info = new QWidgetHostInfo;
    info->m_index = 23;
    info->m_metaObject = &(QDoubleSpinBoxHost::staticMetaObject);
    info->m_name = "doubleSpinbox";
    info->m_showGroup = tr("Input Widgets");
    info->m_showIcon = ":/inner/images/widgets/doublespinbox.png";
    info->m_showName = tr("Double Spinbox");
    return info;
}

void QDoubleSpinBoxHost::setValue(float value)
{
    setPropertyValue("value",value);
}

float QDoubleSpinBoxHost::getValue()
{
    return getPropertyValue("value").toFloat();
}

void QDoubleSpinBoxHost::setSingleStep(float singleStep)
{
    setPropertyValue("singleStep",singleStep);
}

float QDoubleSpinBoxHost::getSingleStep()
{
    return getPropertyValue("singleStep").toFloat();
}

void QDoubleSpinBoxHost::setDecimals(int decimals)
{
    setPropertyValue("decimals",decimals);
}

int QDoubleSpinBoxHost::getDecimals()
{
    return getPropertyValue("decimals").toInt();
}
