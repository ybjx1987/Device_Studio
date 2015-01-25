#include "qplatformcore.h"

#include "qsettingmanager.h"

QPlatformCore * QPlatformCore::m_instance = NULL;

QPlatformCore::QPlatformCore(QObject *parent) : QObject(parent),
    m_settingManager(new QSettingManager)
{
    m_settingManager->load();
}

QPlatformCore::~QPlatformCore()
{

}

QPlatformCore * QPlatformCore::getInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new QPlatformCore;
    }
    return m_instance;
}

QSettingManager* QPlatformCore::getSettingManager()
{
    return m_settingManager;
}
