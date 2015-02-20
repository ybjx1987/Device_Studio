#include "qspinboxhost.h"

#include "../property/qintproperty.h"
#include "../property/qscriptproperty.h"

#include <QSpinBox>

QSpinBoxHost::QSpinBoxHost(QAbstractWidgetHost * parent):
    QAbstractSpinBoxHost(parent)
{

}

void QSpinBoxHost::createObject()
{
    m_object = new QSpinBox;
    m_object->setObjectName("spinbox");
    m_object->setProperty("geometry",QRect(0,0,100,20));
}

void QSpinBoxHost::initProperty()
{
    QAbstractSpinBoxHost::initProperty();

    QAbstractProperty * pro;

    pro = new QIntProperty;
    pro->setName("maximum");
    pro->setShowName(tr("Maximum"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("minimum");
    pro->setShowName(tr("Minimum"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("value");
    pro->setShowName(tr("Value"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("singleStep");
    pro->setShowName(tr("SingleStep"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QScriptProperty;
    pro->setName("valueChanged");
    pro->setShowName(tr("Value Changed"));
    pro->setGroup("Events");
    insertProperty(pro);
}

QAbstractHostInfo* QSpinBoxHost::getHostInfo()
{
    QWidgetHostInfo *info = new QWidgetHostInfo;
    info->m_index = 15;
    info->m_metaObject = &(QSpinBoxHost::staticMetaObject);
    info->m_name = "spinbox";
    info->m_showGroup = tr("Input Widgets");
    info->m_showIcon = ":/inner/images/widgets/spinbox.png";
    info->m_showName = tr("SpinBox");
    return info;
}

void QSpinBoxHost::setValue(int value)
{
    setPropertyValue("value",value);
}

int QSpinBoxHost::getValue()
{
    return getPropertyValue("value").toInt();
}

void QSpinBoxHost::setSingleStep(int singleStep)
{
    setPropertyValue("singleStep",singleStep);
}

int QSpinBoxHost::getSingleStep()
{
    return getPropertyValue("singleStep").toInt();
}
