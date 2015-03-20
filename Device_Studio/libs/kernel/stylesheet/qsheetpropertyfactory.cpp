#include "qsheetpropertyfactory.h"

#include "type/qabstractsheettype.h"
#include "type/qurlsheettype.h"
#include "type/qnumbersheettype.h"
#include "type/qstringsheettype.h"
#include "type/qfontsheettype.h"
#include "type/qbrushsheettype.h"
#include "type/qbordersheettype.h"

QMap<QString,TypeInfo>     QSheetPropertyFactory::m_metaMap;

void QSheetPropertyFactory::registerProperty(const TypeInfo & info)
{
    if(m_metaMap.contains(info.m_name))
    {
        return;
    }

    m_metaMap.insert(info.m_name,info);
}

QAbstractSheetType* QSheetPropertyFactory::createProperty(const QString &name)
{
    if(!m_metaMap.keys().contains(name))
    {
        return NULL;
    }
    TypeInfo info = m_metaMap.value(name);
    QAbstractSheetType *pro = (QAbstractSheetType*)info.m_metaObject.newInstance();
    if(pro != NULL)
    {
        pro->setName(info.m_name);
        pro->setTypeProperty(info.m_property);
    }
    return pro;
}

QStringList QSheetPropertyFactory::getPropertyInfo()
{
    return m_metaMap.keys();
}

void QSheetPropertyFactory::registerInnerProperty()
{
    TypeInfo info;
    info.m_name = "image";
    info.m_metaObject = QUrlSheetType::staticMetaObject;
    registerProperty(info);
    info.m_name = "icon-size";
    info.m_metaObject = QNumberSheetType::staticMetaObject;
    info.m_property = "<Property minValue =\"0\" maxValue=\"100\" suffix=\"px\"/>";
    registerProperty(info);
    info.m_name = "padding-top";
    info.m_metaObject = QNumberSheetType::staticMetaObject;
    info.m_property = "<Property minValue =\"0\" maxValue=\"1000\" suffix=\"px\"/>";
    registerProperty(info);
    info.m_name = "padding-right";
    info.m_metaObject = QNumberSheetType::staticMetaObject;
    info.m_property = "<Property minValue =\"0\" maxValue=\"1000\" suffix=\"px\"/>";
    registerProperty(info);
    info.m_name = "padding-bottom";
    info.m_metaObject = QNumberSheetType::staticMetaObject;
    info.m_property = "<Property minValue =\"0\" maxValue=\"1000\" suffix=\"px\"/>";
    registerProperty(info);
    info.m_name = "padding-left";
    info.m_metaObject = QNumberSheetType::staticMetaObject;
    info.m_property = "<Property minValue =\"0\" maxValue=\"1000\" suffix=\"px\"/>";
    registerProperty(info);
    info.m_name = "border";
    info.m_metaObject = QBorderSheetType::staticMetaObject;
    registerProperty(info);
    info.m_name = "border-top";
    info.m_metaObject = QBorderSheetType::staticMetaObject;
    registerProperty(info);
    info.m_name = "border-right";
    info.m_metaObject = QBorderSheetType::staticMetaObject;
    registerProperty(info);
    info.m_name = "border-left";
    info.m_metaObject = QBorderSheetType::staticMetaObject;
    registerProperty(info);
    info.m_name = "border-bottom";
    info.m_metaObject = QBorderSheetType::staticMetaObject;
    registerProperty(info);
    info.m_name = "font";
    info.m_metaObject = QFontSheetType::staticMetaObject;
    registerProperty(info);
    info.m_name = "color";
    info.m_metaObject = QBrushSheetType::staticMetaObject;
    registerProperty(info);
    info.m_name = "selection-background-color";
    info.m_metaObject = QBrushSheetType::staticMetaObject;
    registerProperty(info);
    info.m_name = "selection-color";
    info.m_metaObject = QBrushSheetType::staticMetaObject;
    registerProperty(info);

    //registerProperty("text-decoration",QTextDecorationSheetType::staticMetaObject);
    //registerProperty("background-color",QBrushSheetType::staticMetaObject);
}
