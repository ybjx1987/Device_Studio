#include "qsoftactionmap.h"

QMap<QString,QAction*> QSoftActionMap::m_idToAction;

void QSoftActionMap::insertAction(const QString &id, QAction *action)
{
    m_idToAction.insert(id,action);
}

QAction* QSoftActionMap::getAction(const QString &id)
{
    return m_idToAction.value(id);
}
