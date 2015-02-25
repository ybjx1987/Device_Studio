#include "qintdatahost.h"

#include "../property/qintproperty.h"

QIntDataHost::QIntDataHost(QAbstractHost * parent):
    QAbstractDataHost(parent)
{

}

QAbstractHostInfo * QIntDataHost::getHostInfo()
{
    QDataHostInfo * info = new QDataHostInfo;
    info->m_name = "dataNumber";
    info->m_showName = "Number";
    info->m_metaObject = &(QIntDataHost::staticMetaObject);
    return info;
}

void QIntDataHost::initProperty()
{
    QAbstractDataHost::initProperty();
    QAbstractProperty * pro;

    setPropertyValue("type","Number");

    pro = new QIntProperty;
    pro->setName("value");
    pro->setShowName(tr("Value"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("minValue");
    pro->setShowName("Minium Value");
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("maxValue");
    pro->setShowName("Maxium Value");
    pro->setGroup("Attributes");
    insertProperty(pro);
}

void QIntDataHost::initDefaultValue()
{
    QAbstractDataHost::initDefaultValue();
    m_object->setProperty("value",0);
    m_object->setProperty("minValue",0);
    m_object->setProperty("maxValue",65535);
}
