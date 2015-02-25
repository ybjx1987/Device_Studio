#include "qfloatdatahost.h"

#include "../property/qfloatproperty.h"

QFloatDataHost::QFloatDataHost(QAbstractHost * parent):
    QAbstractDataHost(parent)
{

}

void QFloatDataHost::initProperty()
{
    QAbstractDataHost::initProperty();

    setPropertyValue("type","Float");

    QAbstractProperty * pro;

    pro = new QFloatProperty;
    pro->setName("value");
    pro->setShowName(tr("Value"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QFloatProperty;
    pro->setName("minValue");
    pro->setShowName(tr("Minium Value"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QFloatProperty;
    pro->setName("maxValue");
    pro->setShowName(tr("Maxium Value"));
    pro->setGroup("Attributes");
    insertProperty(pro);
}

void QFloatDataHost::initDefaultValue()
{
    QAbstractDataHost::initDefaultValue();
    m_object->setProperty("value",0.0);
    m_object->setProperty("minValue",0.0);
    m_object->setProperty("maxValue",65535.0);
}

QAbstractHostInfo * QFloatDataHost::getHostInfo()
{
    QDataHostInfo * info = new QDataHostInfo;
    info->m_showName = "Float";
    info->m_metaObject = &(QFloatDataHost::staticMetaObject);

    return info;
}
