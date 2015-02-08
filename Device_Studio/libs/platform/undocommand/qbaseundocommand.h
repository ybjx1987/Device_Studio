#ifndef QBASEUNDOCOMMAND_H
#define QBASEUNDOCOMMAND_H

#include "../platformlibglobal.h"

#include <QUndoCommand>
#include <QVariant>

class PLATFORM_EXPORT QBaseUndoCommand : public QUndoCommand
{
public:
    QBaseUndoCommand(QUndoCommand* parent=0);
};
#endif // QBASEUNDOCOMMAND_H
