#ifndef QPLATFORMCORE_H
#define QPLATFORMCORE_H

#include "platformlibglobal.h"

#include <QObject>

class QSettingManager;

class PLATFORM_EXPORT QPlatformCore : public QObject
{
    Q_OBJECT
protected:
    explicit QPlatformCore(QObject *parent = 0);
    ~QPlatformCore();

public:
    static QPlatformCore * getInstance();

public:
    QSettingManager * getSettingManager();

protected:
    QSettingManager *m_settingManager;
protected:
    static QPlatformCore * m_instance;
};

#endif // QPLATFORMCORE_H
