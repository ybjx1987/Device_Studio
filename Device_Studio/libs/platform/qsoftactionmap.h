#ifndef QSOFTACTIONMAP_H
#define QSOFTACTIONMAP_H

#include "platformlibglobal.h"

#include <QMap>
#include <QAction>


class PLATFORM_EXPORT QSoftActionMap
{
public:
    static void        insertAction(const QString & id,QAction * action);
    static QAction*    getAction(const QString & id);
protected:
    static QMap<QString,QAction*>      m_idToAction;


};

#endif // QSOFTACTIONMAP_H
