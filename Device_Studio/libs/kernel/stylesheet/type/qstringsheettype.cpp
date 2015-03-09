#include "qstringsheettype.h"

#include "../../xmlnode.h"

QStringSheetType::QStringSheetType(QAbstractSheetType *parent):
    QAbstractSheetType(parent)
{
    setValue("");
}

QStringSheetType::~QStringSheetType()
{

}

QString QStringSheetType::getValueText()
{
    return "\""+getValue().toString()+"\"";
}

void QStringSheetType::toXml(XmlNode *xml)
{
    xml->setProperty("value",getValue().toString());
    QAbstractSheetType::toXml(xml);
}

void QStringSheetType::fromXml(XmlNode *xml)
{
    m_value = xml->getProperty("value");
    QAbstractSheetType::fromXml(xml);
}
