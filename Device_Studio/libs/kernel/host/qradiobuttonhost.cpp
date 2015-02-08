#include "qradiobuttonhost.h"

#include <QRadioButton>
#include <QVariant>

QRadioButtonHost::QRadioButtonHost(QAbstractWidgetHost * parent):
    QAbstractButtonHost(parent)
{

}

void QRadioButtonHost::createObject()
{

    m_object=new QRadioButton();
    m_object->setObjectName("radiobutton");
    m_object->setProperty("text","radio button");
}

void QRadioButtonHost::initProperty()
{
    QAbstractButtonHost::initProperty();
    removeProperty("checkable");
}

QWidgetHostInfo* QRadioButtonHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo();
    info->m_metaObject = &(QRadioButtonHost::staticMetaObject);
    info->m_index = 22;
    info->m_showGroup = tr("Buttons");
    info->m_showIcon = ":/inner/images/widgets/radiobutton.png";
    info->m_showName = tr("Radio Button");
    info->m_name = "radiobutton";
    return info;
}
