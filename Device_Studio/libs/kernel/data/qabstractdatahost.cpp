#include "qabstractdatahost.h"

QAbstractDataHost::QAbstractDataHost():
    QAbstractHost(NULL)
{

}

QVariant QAbstractDataHost::getValue()
{
    return m_value;
}

void QAbstractDataHost::setValue(const QVariant &value)
{
    if(!equal(value))
    {
        m_value = value;
        emit valueChanged();
    }
}

QString QAbstractDataHost::getValueText()
{
    return m_value.toString();
}

bool QAbstractDataHost::equal(const QVariant &value)
{
    return m_value == value;
}

void QAbstractDataHost::setName(const QString &name)
{
    if(m_name != name)
    {
        m_name = name;
        emit propertyChanged("name");
    }
}

QString QAbstractDataHost::getName()
{
    return m_name;
}

void QAbstractDataHost::setNeedSave(bool needSave)
{
    if(m_needSave != needSave)
    {
        m_needSave = needSave;
        emit propertyChanged("needSave");
    }
}

bool QAbstractDataHost::getNeedSave()
{
    return m_needSave;
}

void QAbstractDataHost::createObject()
{
    m_object = new QObject;
}

void QAbstractDataHost::setExplanation(const QString &explanation)
{
    if(m_explanation != explanation)
    {
        m_explanation = explanation;
        emit propertyChanged("explanation");
    }
}

void QAbstractDataHost::initProperty()
{
    QAbstractHost::initProperty();

    QAbstractProperty * pro;

    removeProperty("objectName");
}

QString QAbstractDataHost::getUuid()
{
    return m_uuid;
}
