#include "qpropertyeditundocommand.h"

#include "qundocommandid.h"

#include "../../kernel/host/qabstracthost.h"
#include "../../kernel/qproject.h"
#include "../qsoftcore.h"

QPropertyEditUndoCommand::QPropertyEditUndoCommand(const QString &hostUuid,
                                                   const QString &propertyName,
                                                   const QVariant &newValue,
                                                   const QVariant &oldValue,
                                                   QUndoCommand *parent):
    QBaseUndoCommand(parent),
    m_hostUuid(hostUuid),
    m_propertyName(propertyName),
    m_newValue(newValue),
    m_oldValue(oldValue)
{

}

QPropertyEditUndoCommand::~QPropertyEditUndoCommand()
{

}

int QPropertyEditUndoCommand::id() const
{
    return PROPERTY_EDIT;
}

void QPropertyEditUndoCommand::redo()
{
    QProject * project = QSoftCore::getInstance()->getProject();
    QAbstractHost * host = project->getHostByUuid(m_hostUuid);
    if(host != NULL)
    {
        host->setPropertyValue(m_propertyName,m_newValue);
    }
}

void QPropertyEditUndoCommand::undo()
{
    QProject * project = QSoftCore::getInstance()->getProject();
    QAbstractHost * host = project->getHostByUuid(m_hostUuid);
    if(host != NULL)
    {
        host->setPropertyValue(m_propertyName,m_oldValue);
    }
}

bool QPropertyEditUndoCommand::mergeWith(const QUndoCommand *other)
{
    QPropertyEditUndoCommand* cmd = (QPropertyEditUndoCommand*)other;

    if(cmd->m_hostUuid == m_hostUuid && cmd->m_propertyName == m_propertyName)
    {
        m_newValue = cmd->m_newValue;
        return true;
    }
    else
    {
        return false;
    }
}
