#include "qpropertyeditundocommandmore.h"

#include "qpropertyeditundocommand.h"
#include "qundocommandid.h"

QPropertyEditUndoCommandMore::QPropertyEditUndoCommandMore(
        const QString & propertyName,QUndoCommand* parent):
    QBaseUndoCommand(parent),
    m_propertyName(propertyName)
{

}

QPropertyEditUndoCommandMore::~QPropertyEditUndoCommandMore()
{

}

void QPropertyEditUndoCommandMore::add(const QString &hostUuid, const QVariant &oldValue, const QVariant &newValue)
{
    QPropertyEditUndoCommand *cmd = new QPropertyEditUndoCommand(
                hostUuid,m_propertyName,
                newValue,oldValue,this);

    m_children.append(cmd);

}

int QPropertyEditUndoCommandMore::id()const
{
    return PROPERTY_EDIT_MORE;
}

bool QPropertyEditUndoCommandMore::mergeWith(const QUndoCommand *other)
{
    QPropertyEditUndoCommandMore* cmd = (QPropertyEditUndoCommandMore*)other;

    if(cmd->m_propertyName != m_propertyName)
    {
        return false;
    }

    if(cmd->m_hostUuids != m_hostUuids)
    {
        return false;
    }

    int count = m_children.size();

    for(int i= 0;i<count;i++)
    {
        QPropertyEditUndoCommand *cmd1 = m_children.at(i);
        QPropertyEditUndoCommand *cmd2 = cmd->m_children.at(i);
        cmd1->mergeWith(cmd2);
    }
    return true;
}
