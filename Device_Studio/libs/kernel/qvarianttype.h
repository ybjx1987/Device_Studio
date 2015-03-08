#ifndef QVARIANTTYPE
#define QVARIANTTYPE

#include <QString>
#include <QVariant>
#include <QList>
#include <QGradient>

struct tagComboItem
{
    QString     m_text;
    QString     m_icon;
    QVariant    m_value;

    bool operator == (const tagComboItem & item) const
    {
        return (m_value == item.m_value);
    }

    bool operator !=(const tagComboItem & item) const
    {
        return (m_value != item.m_value);
    }
};

typedef QList<tagComboItem> ComboItems;
Q_DECLARE_METATYPE(ComboItems)

class tagMemeryValueInfo
{
public:
    QString     m_propertyName;
    QString     m_dataUuid;
    bool operator ==(const tagMemeryValueInfo &info) const
    {
        return (info.m_propertyName==m_propertyName
                && info.m_dataUuid==m_dataUuid);
    }

    bool operator !=(const tagMemeryValueInfo &info) const
    {
        return !((*this) == info);
    }
};
typedef QList<tagMemeryValueInfo> MemeryValueItems;
Q_DECLARE_METATYPE(MemeryValueItems)

class tagFontSheetType
{
public:
    QString m_name;
    int     m_size;
    QString m_style;
    bool operator ==(const tagFontSheetType &type) const
    {
        return (type.m_name==m_name
                && type.m_size==m_size
                && type.m_style==m_style);
    }

    bool operator !=(const tagFontSheetType &type) const
    {
        return !((*this) == type);
    }
};
Q_DECLARE_METATYPE(tagFontSheetType)

Q_DECLARE_METATYPE(QGradient)

class tagBrushSheetType
{
public:
    QString m_type;
    QVariant m_value;
    QString m_alpha;

    bool operator ==(const tagBrushSheetType &type) const
    {
        if(m_type != type.m_type || m_alpha != type.m_alpha)
        {
            return false;
        }
        if(m_type == "Color")
        {
            QColor c1 = m_value.value<QColor>();
            QColor c2 = type.m_value.value<QColor>();
            return c1 == c2;
        }
        else
        {
            QGradient g1 = m_value.value<QGradient>();
            QGradient g2 = type.m_value.value<QGradient>();
            return g1 == g2;
        }
    }

    bool operator !=(const tagBrushSheetType &type) const
    {
        return !((*this) == type);
    }
};
Q_DECLARE_METATYPE(tagBrushSheetType)

#endif // QVARIANTTYPE

