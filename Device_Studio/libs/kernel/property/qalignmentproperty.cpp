#include "qalignmentproperty.h"

#include "qenumproperty.h"

#include "../qvarianttype.h"
#include "../xmlnode.h"

QAlignmentProperty::QAlignmentProperty(QAbstractProperty * parent):
    QAbstractProperty(parent)
{

    m_horizonta = new QEnumProperty(this);
    m_horizonta->setShowName(tr("Horizonta"));
    m_horizonta->setName("horizonta");

    ComboItems items;
    tagComboItem item;
    item.m_text=tr("AlignLeft");
    item.m_value=Qt::AlignLeft;
    items.append(item);

    item.m_text=tr("AlignRight");
    item.m_value=Qt::AlignRight;
    items.append(item);

    item.m_text=tr("AlignHCenter");
    item.m_value=Qt::AlignHCenter;
    items.append(item);

    m_horizonta->setProperty("items",QVariant::fromValue<ComboItems>(items));

    m_vertical = new QEnumProperty(this);
    m_vertical->setShowName(tr("Vertical"));
    m_vertical->setName("Vertical");

    items.clear();
    item.m_text=tr("AlignTop");
    item.m_value=Qt::AlignTop;
    items.append(item);

    item.m_text=tr("AlignBottom");
    item.m_value=Qt::AlignBottom;
    items.append(item);

    item.m_text=tr("AlignVCenter");
    item.m_value=Qt::AlignVCenter;
    items.append(item);

    m_vertical->setProperty("items",QVariant::fromValue<ComboItems>(items));
}

QString QAlignmentProperty::getValueText()
{
    return m_horizonta->getValueText()+" | "+m_vertical->getValueText();
}

QIcon QAlignmentProperty::getValueIcon()
{
    return QIcon();
}

void QAlignmentProperty::setValue(const QVariant &value)
{
    int align = value.toInt();
    disconnectUpdateValue();
    m_horizonta->setValue(align & Qt::AlignHorizontal_Mask);
    m_vertical->setValue(align & Qt::AlignVertical_Mask);
    connectUpdateValue();
    QAbstractProperty::setValue(value);
}

void QAlignmentProperty::makeValue(XmlNode *xml)
{
    setName(xml->getProperty("name"));
}

void QAlignmentProperty::writeValue(XmlNode *xml)
{
    xml->setProperty("name",getName());
}
