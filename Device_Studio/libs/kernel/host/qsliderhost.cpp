#include "qsliderhost.h"

#include "../property/qenumproperty.h"
#include "../qvarianttype.h"

#include <QSlider>

QSliderHost::QSliderHost(QAbstractWidgetHost * parent):
    QAbstractSliderHost(parent)
{

}

QAbstractHostInfo *QSliderHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo();
    info->m_metaObject = &(QSliderHost::staticMetaObject);
    info->m_index = 13;
    info->m_showGroup = tr("Input Widgets");
    info->m_showIcon = ":/inner/images/widgets/hslider.png";
    info->m_showName = tr("Slider");
    info->m_name = "slider";
    return info;
}

void QSliderHost::createObject()
{
    m_object = new QSlider;
    m_object->setObjectName("slider");
    m_object->setProperty("geometry",QRect(0,0,100,30));
}

void QSliderHost::initProperty()
{
    QAbstractSliderHost::initProperty();

    QAbstractProperty * pro;

    pro = new QEnumProperty;
    pro->setName("tickPosition");
    pro->setShowName(tr("Tick Position"));
    pro->setGroup("Attributes");
    ComboItems items;
    tagComboItem item;
    item.m_text="NoTicks";
    item.m_value=QSlider::NoTicks;
    items.append(item);

    item.m_text="TicksAbove";
    item.m_value=QSlider::TicksAbove;
    items.append(item);

    item.m_text="TicksBelow";
    item.m_value=QSlider::TicksBelow;
    items.append(item);

    item.m_text="TicksLeft";
    item.m_value=QSlider::TicksLeft;
    items.append(item);

    item.m_text="TicksRight";
    item.m_value=QSlider::TicksRight;
    items.append(item);

    item.m_text="TicksBothSides";
    item.m_value=QSlider::TicksBothSides;
    items.append(item);

    QVariant v;
    v.setValue<ComboItems>(items);
    pro->setProperty("items",QVariant::fromValue<ComboItems>(items));
    insertProperty(pro);
}
