#include "qdialhost.h"

#include "../property/qabstractproperty.h"

#include <QDial>

QDialHost::QDialHost(QAbstractWidgetHost * parent):
    QAbstractSliderHost(parent)
{

}

void QDialHost::createObject()
{
    m_object = new QDial();
    m_object->setObjectName("dial");
    m_object->setProperty("geometry",QRect(0,0,60,60));
}

void QDialHost::initProperty()
{
    QAbstractSliderHost::initProperty();

    QAbstractProperty * pro;
    pro = getProperty("geometry");
    pro->setDefaultValue(QRect(0,0,60,60));
}

QAbstractHostInfo* QDialHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo();
    info->m_metaObject = &(QDialHost::staticMetaObject);
    info->m_index = 12;
    info->m_showGroup = tr("Input Widgets");
    info->m_showIcon = ":/inner/images/widgets/dial.png";
    info->m_showName = tr("Dial");
    info->m_name = "dial";
    return info;
}
