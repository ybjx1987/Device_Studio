#include "qwidgethost.h"

#include "../property/qabstractproperty.h"
#include "../property/qboolproperty.h"

#include <QWidget>
#include <QVariant>

QWidgetHost::QWidgetHost(QAbstractWidgetHost *parent):
    QAbstractWidgetHost(parent)
{
    setProperty("needFrame",true);
    setProperty("acceptDrop",true);
    setProperty("editProperty","objectName");
}

void QWidgetHost::createObject()
{
    m_object = new QWidget();
    m_object->setObjectName("widget");
}

void QWidgetHost::setVisible(bool visible)
{
    setPropertyValue("visible",visible);
}

bool QWidgetHost::getVisible()
{
    return getPropertyValue("visible").toBool();
}

void QWidgetHost::setFocus()
{
    ((QWidget*)m_object)->setFocus();
}

void QWidgetHost::killFocus()
{
    ((QWidget*)m_object)->clearFocus();
}

void QWidgetHost::initProperty()
{
    QAbstractWidgetHost::initProperty();

    QAbstractProperty *pro;

    pro = new QBoolProperty();
    pro->setName("visible");
    pro->setShowName(tr("Visible"));
    pro->setCanSame(true);
    pro->setGroup("Attributes");
    insertProperty(pro,2);
}

QAbstractHostInfo* QWidgetHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo();
    info->m_metaObject = &(QWidgetHost::staticMetaObject);
    info->m_index = 1;
    info->m_showGroup = tr("Containners");
    info->m_showName = tr("Widget");
    info->m_showIcon = ":/inner/images/widgets/widget.png";
    return info;
}
