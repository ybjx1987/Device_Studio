#include "qabstractspinboxhost.h"

#include "../property/qboolproperty.h"
#include "../property/qenumproperty.h"
#include "../qvarianttype.h"

#include <QAbstractSpinBox>

QAbstractSpinBoxHost::QAbstractSpinBoxHost(QAbstractWidgetHost * parent):
    QWidgetHost(parent)
{
    setProperty("needFrame",false);
    setProperty("acceptDrop",false);
}

void QAbstractSpinBoxHost::initProperty()
{
    QWidgetHost::initProperty();

    QAbstractProperty * pro;

    pro = new QBoolProperty;
    pro->setName("frame");
    pro->setShowName(tr("Frame"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QBoolProperty;
    pro->setName("wrapping");
    pro->setShowName(tr("Wrapping"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QBoolProperty;
    pro->setName("readOnly");
    pro->setShowName(tr("ReadOnly"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QEnumProperty;
    pro->setName("buttonSymbols");
    pro->setShowName(tr("Button Symbols"));
    pro->setGroup("Attributes");
    ComboItems items;
    tagComboItem item;

    item.m_text=tr("UpDownArrows");
    item.m_value=QAbstractSpinBox::UpDownArrows;
    items.append(item);

    item.m_text=tr("NoButtons");
    item.m_value=QAbstractSpinBox::NoButtons;
    items.append(item);

    pro->setProperty("items",QVariant::fromValue<ComboItems>(items));
    insertProperty(pro);

    pro = new QEnumProperty;
    pro->setName("alignment");
    pro->setShowName(tr("Alignment"));
    pro->setGroup("Attributes");

    items.clear();
    item.m_text=tr("AlignLeft");
    item.m_value=Qt::AlignLeft;
    items.append(item);

    item.m_text=tr("AlignRight");
    item.m_value=Qt::AlignRight;
    items.append(item);

    item.m_text=tr("AlignHCenter");
    item.m_value=Qt::AlignHCenter;
    items.append(item);

    pro->setProperty("items",QVariant::fromValue<ComboItems>(items));
    insertProperty(pro);
}

void QAbstractSpinBoxHost::setFrame(bool frame)
{
    setPropertyValue("frame",frame);
}

bool QAbstractSpinBoxHost::getFrame()
{
    return getPropertyValue("frame").toBool();
}

void QAbstractSpinBoxHost::setWrapping(bool wrapping)
{
    setPropertyValue("wrapping",wrapping);
}

bool QAbstractSpinBoxHost::getWrapping()
{
    return getPropertyValue("wrapping").toBool();
}

void QAbstractSpinBoxHost::setReadOnly(bool readonly)
{
    setPropertyValue("readonly",readonly);
}

bool QAbstractSpinBoxHost::getReadOnly()
{
    return getPropertyValue("readonly").toBool();
}

void QAbstractSpinBoxHost::setButtonSymbols(int buttonSymbols)
{
    setPropertyValue("buttonSymbols",buttonSymbols);
}

int QAbstractSpinBoxHost::getButtonSymbols()
{
    return getPropertyValue("buttonSymbols").toInt();
}

void QAbstractSpinBoxHost::setAlignment(int alignment)
{
    setPropertyValue("alignment",alignment);
}

int QAbstractSpinBoxHost::getAlignment()
{
    return getPropertyValue("alignment").toInt();
}
