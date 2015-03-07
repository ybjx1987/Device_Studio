#include "qsheetpropertyfactory.h"

#include "type/qabstractsheettype.h"
#include "type/qurlsheettype.h"
#include "type/qnumbersheettype.h"
#include "type/qlengthsheettype.h"
#include "type/qalignmentsheettype.h"
#include "type/qrepeatsheettype.h"
#include "type/qborderstylesheettype.h"
#include "type/qfontstylesheettype.h"
#include "type/qstringsheettype.h"
#include "type/qtextdecorationsheettype.h"
#include "type/qfontsheettype.h"

QMap<QString,QMetaObject>     QSheetPropertyFactory::m_metaMap;

void QSheetPropertyFactory::registerProperty(const QString & name,
                                             QMetaObject meta)
{
    if(m_metaMap.contains(name))
    {
        return;
    }

    m_metaMap.insert(name,meta);
}

QAbstractSheetType* QSheetPropertyFactory::createProperty(const QString &name)
{
    if(!m_metaMap.keys().contains(name))
    {
        return NULL;
    }
    QMetaObject meta = m_metaMap.value(name);
    QAbstractSheetType *pro = (QAbstractSheetType*)meta.newInstance();
    if(pro != NULL)
    {
        pro->setName(name);
    }
    return pro;
}

QStringList QSheetPropertyFactory::getPropertyInfo()
{
    return m_metaMap.keys();
}

void QSheetPropertyFactory::registerInnerProperty()
{
    registerProperty("background-image",QUrlSheetType::staticMetaObject);
    registerProperty("image",QUrlSheetType::staticMetaObject);
    registerProperty("border-top-width",QLengthSheetType::staticMetaObject);
    registerProperty("border-left-width",QLengthSheetType::staticMetaObject);
    registerProperty("border-right-width",QLengthSheetType::staticMetaObject);
    registerProperty("border-bottom-width",QLengthSheetType::staticMetaObject);
    registerProperty("icon-size",QLengthSheetType::staticMetaObject);
    registerProperty("margin-top",QLengthSheetType::staticMetaObject);
    registerProperty("margin-left",QLengthSheetType::staticMetaObject);
    registerProperty("margin-right",QLengthSheetType::staticMetaObject);
    registerProperty("margin-bottom",QLengthSheetType::staticMetaObject);
    registerProperty("max-width",QLengthSheetType::staticMetaObject);
    registerProperty("min-width",QLengthSheetType::staticMetaObject);
    registerProperty("max-height",QLengthSheetType::staticMetaObject);
    registerProperty("min-height",QLengthSheetType::staticMetaObject);
    registerProperty("opacity",QNumberSheetType::staticMetaObject);
    registerProperty("padding-top",QLengthSheetType::staticMetaObject);
    registerProperty("padding-left",QLengthSheetType::staticMetaObject);
    registerProperty("padding-right",QLengthSheetType::staticMetaObject);
    registerProperty("padding-bottom",QLengthSheetType::staticMetaObject);
    registerProperty("background-position",QAlignmentSheetType::staticMetaObject);
    registerProperty("image-position",QAlignmentSheetType::staticMetaObject);
    registerProperty("subcontrol-position",QAlignmentSheetType::staticMetaObject);
    registerProperty("text-align",QAlignmentSheetType::staticMetaObject);
    registerProperty("background-repeat",QRepeatSheetType::staticMetaObject);
    registerProperty("border-style",QBorderStyleSheetType::staticMetaObject);
    registerProperty("border-top-style",QBorderStyleSheetType::staticMetaObject);
    registerProperty("border-left-style",QBorderStyleSheetType::staticMetaObject);
    registerProperty("border-bottom-style",QBorderStyleSheetType::staticMetaObject);
    registerProperty("border-right-style",QBorderStyleSheetType::staticMetaObject);
    registerProperty("font-style",QFontStyleSheetType::staticMetaObject);
    registerProperty("font-size",QLengthSheetType::staticMetaObject);
    registerProperty("font-family",QStringSheetType::staticMetaObject);
    registerProperty("text-decoration",QTextDecorationSheetType::staticMetaObject);
    registerProperty("font",QFontSheetType::staticMetaObject);

}
