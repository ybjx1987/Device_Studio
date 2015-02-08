#include "qpushbuttonhost.h"

#include <QPushButton>
#include <QVariant>

QPushButtonHost::QPushButtonHost(QAbstractWidgetHost * parent):
    QAbstractButtonHost(parent)
{

}

void QPushButtonHost::createObject()
{

    m_object=new QPushButton();
    m_object->setObjectName("pushbutton");
    m_object->setProperty("text","button");
}

void QPushButtonHost::initProperty()
{
    QAbstractButtonHost::initProperty();
}

QWidgetHostInfo* QPushButtonHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo();
    info->m_metaObject = &(QPushButtonHost::staticMetaObject);
    info->m_index = 20;
    info->m_showGroup = tr("Buttons");
    info->m_showIcon = ":/inner/images/widgets/pushbutton.png";
    info->m_showName = tr("Push Button");
    info->m_name = "pushbutton";
    return info;
}
