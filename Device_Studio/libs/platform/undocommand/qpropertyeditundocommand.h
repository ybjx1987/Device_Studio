#ifndef QPROPERTYEDITUNDOCOMMAND_H
#define QPROPERTYEDITUNDOCOMMAND_H

#include "qbaseundocommand.h"



class QPropertyEditUndoCommand : public QBaseUndoCommand
{
public:
    QPropertyEditUndoCommand(const QString & hostUuid,
                             const QString & propertyName,
                             const QVariant & newValue,
                             const QVariant & oldValue,
                             QUndoCommand *parent = NULL);
    ~QPropertyEditUndoCommand();
public:
    int     id() const;

    void    redo();
    void    undo();

    bool    mergeWith(const QUndoCommand *other);
protected:
    QString         m_propertyName;
    QString         m_hostUuid;
    QVariant        m_newValue;
    QVariant        m_oldValue;
};

#endif // QPROPERTYEDITUNDOCOMMAND_H
