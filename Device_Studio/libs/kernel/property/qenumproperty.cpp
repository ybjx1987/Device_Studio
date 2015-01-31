#include "qenumproperty.h"

#include "../qvarianttype.h"

QEnumProperty::QEnumProperty(QAbstractProperty * parent):
    QAbstractProperty(parent)
{
    setType("ENUM");
}

QString QEnumProperty::getValueText()
{
    ComboItems items = property("items").value<ComboItems>();
    foreach(tagComboItem item,items)
    {
        if(equal(item.m_value))
        {
            return item.m_text;
        }
    }
    return "";
}

QIcon QEnumProperty::getValueIcon()
{
    ComboItems items = this->property("items").value<ComboItems>();
    foreach(tagComboItem item,items)
    {
        if(equal(item.m_value))
        {
            return QIcon(item.m_icon);
        }
    }
    return QIcon();
}

