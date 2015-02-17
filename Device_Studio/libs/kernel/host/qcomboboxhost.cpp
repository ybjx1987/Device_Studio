#include "qcomboboxhost.h"

#include "../../../libs/kernel/property/qintproperty.h"
#include "../../../libs/kernel/property/qscriptproperty.h"

#include <QComboBox>

QComboBoxHost::QComboBoxHost(QAbstractWidgetHost* parent):
    QWidgetHost(parent)
{
    setProperty("needFrame",false);
    setProperty("acceptDrop",false);
}

void QComboBoxHost::createObject()
{
    m_object = new QComboBox;
    m_object->setObjectName("comboBox");
    m_object->setProperty("geometry",QRect(0,0,100,20));
}

void QComboBoxHost::initProperty()
{
    QWidgetHost::initProperty();

    QAbstractProperty * pro;

    pro = new QIntProperty;
    pro->setName("currentIndex");
    pro->setShowName(tr("Current Index"));
    pro->setGroup("Attributes");
    insertProperty(pro,1);

    pro = new QIntProperty;
    pro->setName("maxVisibleItems");
    pro->setShowName(tr("MaxVisibleItems"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QScriptProperty;
    pro->setName("currentIndexChanged");
    pro->setShowName(tr("Current Index Changed"));
    pro->setGroup("Events");
    insertProperty(pro);
}

QWidgetHostInfo* QComboBoxHost::getHostInfo()
{
    QWidgetHostInfo *info = new QWidgetHostInfo();
    info->m_metaObject = &(QComboBoxHost::staticMetaObject);
    info->m_index = 11;
    info->m_showGroup = tr("Input Widgets");
    info->m_showIcon = ":/inner/images/widgets/combobox.png";
    info->m_showName = tr("ComboBox");
    info->m_name = "combobox";
    return info;
}
