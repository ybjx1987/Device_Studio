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

    bool operator == (const tagComboItem & item)
    {
        return (m_value == item.m_value);
    }

    bool operator !=(const tagComboItem & item)
    {
        return (m_value != item.m_value);
    }
};

typedef QList<tagComboItem> ComboItems;
Q_DECLARE_METATYPE(ComboItems)


#endif // QVARIANTTYPE

