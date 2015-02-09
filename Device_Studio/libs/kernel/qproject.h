#ifndef QPROJECT_H
#define QPROJECT_H

#include "kernellibglobal.h"

#include <QObject>

class QProjectHost;

enum enProjectStatus
{
    PS_CLOSED,
    PS_OPENING,
    PS_OPENED,
    PS_BOTTOM
};

class KERNEL_EXPORT QProject :public QObject
{
    Q_OBJECT
public:
    QProject();
    ~QProject();

    bool    open(const QString &proFileName);

    void    close();

    QProjectHost * getProjectHost();

    enProjectStatus getProjectStatus();
protected:
    void        setProjectStatus(enProjectStatus newStatus);
signals:
    void        projectOpened();
    void        projectClosed();

    void        projectStatusChanged(enProjectStatus newStatus);
protected:
    QProjectHost    *m_projectHost;

    enProjectStatus m_projectStatus;
};

#endif // QPROJECT_H
