#include "qaddhostundocommand.h"

#include "qundocommandid.h"

#include "../../kernel/host/qabstracthost.h"

QAddHostUndoCommand::QAddHostUndoCommand(QAbstractHost *parentHost,
                                         QAbstractHost *host,
                                         int index,
                                         enAddHostType type,
                                         QUndoCommand *parent):
    QBaseUndoCommand(parent),
    m_parentHost(parentHost),
    m_host(host),
    m_index(index),
    m_type(type)
{
}

QAddHostUndoCommand::~QAddHostUndoCommand()
{
    if(m_type==AHT_ADD)
    {
        delete m_host;
    }
}

int QAddHostUndoCommand::id()const
{
    return HOST_ADD_AND_REMOVE;
}

void QAddHostUndoCommand::redo()
{
    QBaseUndoCommand::redo();
    if(m_type==AHT_ADD)
    {
        add();
    }
    else if(m_type==AHT_REMOVE)
    {
        remove();
    }
}

void QAddHostUndoCommand::undo()
{
    QBaseUndoCommand::undo();
    if(m_type==AHT_ADD)
    {
        remove();
    }
    else if(m_type==AHT_REMOVE)
    {
        add();
    }
}

void QAddHostUndoCommand::add()
{
    if(m_parentHost!=NULL)
    {
        m_parentHost->insertHost(m_host,m_index);
    }
}

void QAddHostUndoCommand::remove()
{
    if(m_parentHost!=NULL)
    {
        m_parentHost->removeHost(m_host);
    }
}


