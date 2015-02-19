#ifndef QLANGUAGEID_H
#define QLANGUAGEID_H

#include "platformlibglobal.h"

#include <QString>

class PLATFORM_EXPORT QLanguageInfo
{
public:
    QString     m_icon;
    QString     m_name;
    QString     m_id;
};

class PLATFORM_EXPORT QLanguageID
{
public:
    static void load();
    static QList<QLanguageInfo> getLanguageInfos();
    static QLanguageInfo        getLanguageInfo(const QString &id);
protected:
    static QList<QLanguageInfo>     m_languageInfos;
};

#endif // QLANGUAGEID_H
