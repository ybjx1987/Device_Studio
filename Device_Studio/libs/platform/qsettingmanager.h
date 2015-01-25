#ifndef QSETTINGMANAGER_H
#define QSETTINGMANAGER_H

#include "platformlibglobal.h"

#include <QMap>
#include <QVariant>

class PLATFORM_EXPORT QSettingManager
{
public:
    void    setValue(const QString &name,const QVariant &value);
    QVariant getValue(const QString &name,const QVariant &def=QVariant());

    void    save();
    void    load();
protected:
    QString variantToString(const QVariant & value);
    QVariant stringToVariant(const QString & value);
    QStringList splitArgs(const QString &s, int idx);
    void unescapedString(const QString &value,QByteArray &result);
    void escapedString(const QByteArray &array, QString &result);
protected:
    QMap<QString,QVariant>           m_settings;
};

#endif // QSETTINGMANAGER_H
