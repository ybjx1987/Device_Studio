#ifndef QADDHOSTUNDOCOMMAND_H
#define QADDHOSTUNDOCOMMAND_H

#include "qbaseundocommand.h"

#include <QMap>

class QAbstractHost;

enum enAddHostType
{
    AHT_ADD,
    AHT_REMOVE
};

class PLATFORM_EXPORT QAddHostUndoCommand: public QBaseUndoCommand
{
public:
    QAddHostUndoCommand(QAbstractHost *parentHost,
                        QAbstractHost *host,
                        int            index,
                        enAddHostType type,
                        QUndoCommand* parent=0);
    ~QAddHostUndoCommand();

    void    redo();
    void    undo();

    int     id()const;

protected:
    void    add();
    void    remove();
protected:
    QAbstractHost       *m_parentHost;
    QAbstractHost*      m_host;
    int                 m_index;
    enAddHostType       m_type;
};


#endif // QADDHOSTUNDOCOMMAND_H
