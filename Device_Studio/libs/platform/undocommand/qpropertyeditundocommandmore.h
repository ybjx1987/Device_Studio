#ifndef QPROPERTYEDITUNDOCOMMANDMORE_H
#define QPROPERTYEDITUNDOCOMMANDMORE_H

#include "qpropertyeditundocommand.h"

#include <QStringList>

class QPropertyEditUndoCommand;

class QPropertyEditUndoCommandMore: public QBaseUndoCommand
{
public:
    QPropertyEditUndoCommandMore(const QString &proeprtyName,QUndoCommand * parent = NULL);
    ~QPropertyEditUndoCommandMore();

    void    add(const QString &hostUuid,
                const QVariant & oldValue,
                const QVariant & newValue);

    int     id() const;

    bool    mergeWith(const QUndoCommand *other);
protected:
    QStringList     m_hostUuids;

    QString         m_propertyName;

    QList<QPropertyEditUndoCommand*>      m_children;
};

#endif // QPROPERTYEDITUNDOCOMMANDMORE_H
