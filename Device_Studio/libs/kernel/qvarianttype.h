#ifndef QVARIANTTYPE
#define QVARIANTTYPE

#include <QString>
#include <QVariant>
#include <QList>

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

#endif // QVARIANTTYPE

