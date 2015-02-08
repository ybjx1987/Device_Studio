#include "qformhost.h"

#include "../property/qrectproperty.h"

#include <QWidget>

QFormHost::QFormHost(QAbstractWidgetHost * parent):
    QAbstractWidgetHost(parent)
{

}

QAbstractHostInfo* QFormHost::getHostInfo()
{
    QAbstractHostInfo * info = new QAbstractHostInfo();
    info->m_metaObject = &(QFormHost::staticMetaObject);
    info->m_name = "form";
    info->m_type = "form";
    return info;
}

void QFormHost::createObject()
{
    m_object = new QWidget;
    m_object->setObjectName("form");
    m_object->setProperty("geometry",QRect(0,0,800,600));
}

void QFormHost::initProperty()
{
    QAbstractWidgetHost::initProperty();

    QRectProperty * pro;
    pro = (QRectProperty*)getProperty("geometry");
    pro->setSizeType(true);

    removeProperty("enabled");
    removeProperty("level");
    removeProperty("focusPolicy");
}
