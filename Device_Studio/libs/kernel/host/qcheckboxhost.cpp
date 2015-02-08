#include "qcheckboxhost.h"

#include "../property/qboolproperty.h"
#include "../property/qscriptproperty.h"

#include <QCheckBox>
#include <QVariant>

QCheckBoxHost::QCheckBoxHost(QAbstractWidgetHost * parent):
    QAbstractButtonHost(parent)
{

}

void QCheckBoxHost::createObject()
{
    m_object = new QCheckBox();
    m_object->setObjectName("checkbox");
    m_object->setProperty("text","checkbox");
    m_object->setProperty("geometry",QRect(0,0,100,30));
}

void QCheckBoxHost::initProperty()
{
    QAbstractButtonHost::initProperty();

    removeProperty("clicked");
    removeProperty("checkable");
    QAbstractProperty * pro;

    pro = new QBoolProperty();
    pro->setName("tristate");
    pro->setShowName(tr("Tristate"));
    pro->setGroup("Attributes");
    insertProperty(pro,2);

    pro = new QScriptProperty();
    pro->setName("stateChanged");
    pro->setShowName(tr("StateChanged"));
    pro->setGroup("Events");
    insertProperty(pro);
}

QWidgetHostInfo* QCheckBoxHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo();
    info->m_metaObject = &(QCheckBoxHost::staticMetaObject);
    info->m_index = 21;
    info->m_showGroup = tr("Buttons");
    info->m_showIcon = ":/inner/images/widgets/checkbox.png";
    info->m_showName = tr("Checkbox");
    info->m_name = "checkbox";
    return info;
}

void QCheckBoxHost::setTristate(bool tristate)
{
    setPropertyValue("tristate",tristate);
}

bool QCheckBoxHost::getTristate()
{
    return getPropertyValue("tristate").toBool();
}
