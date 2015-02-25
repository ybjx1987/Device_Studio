#include "qabstractdatahost.h"

#include "../property/qabstractproperty.h"
#include "../property/qbytearrayproperty.h"
#include "../property/qboolproperty.h"
#include "../property/qintproperty.h"

QAbstractDataHost::QAbstractDataHost(QAbstractHost * parent):
    QAbstractHost(parent)
{

}

QVariant QAbstractDataHost::getValue()
{
    return getPropertyValue("value");
}

void QAbstractDataHost::setValue(const QVariant &value)
{
    setPropertyValue("value",value);
}

bool QAbstractDataHost::equal(const QVariant &value)
{
    QAbstractProperty* pro = getProperty("value");
    return pro->equal(value);
}


void QAbstractDataHost::createObject()
{
    m_object = new QObject;
    initDefaultValue();
}

void QAbstractDataHost::initProperty()
{
    QAbstractHost::initProperty();

    QAbstractProperty * pro;

    pro = new QBoolProperty;
    pro->setName("needSave");
    pro->setShowName(tr("Need Save"));
    pro->setGroup("Attribute");
    insertProperty(pro);

    pro = new QByteArrayProperty;
    pro->setName("type");
    pro->setShowName("Type");
    pro->setGroup("Attributes");
    pro->setEditable(false);
    insertProperty(pro);

    pro = new QByteArrayProperty;
    pro->setName("explanation");
    pro->setShowName(tr("Explanation"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty;
    pro->setName("savePeriod");
    pro->setShowName(tr("Save Period(ms)"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QBoolProperty;
    pro->setName("hold");
    pro->setShowName(tr("Hold"));
    pro->setGroup("Attributes");
    insertProperty(pro);

}

void QAbstractDataHost::initDefaultValue()
{
    m_object->setProperty("needSave",false);
    m_object->setProperty("hold",false);
    m_object->setProperty("savePeriod",1000);
}
