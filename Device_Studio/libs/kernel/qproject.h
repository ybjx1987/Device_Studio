#ifndef QPROJECT_H
#define QPROJECT_H

#include "kernellibglobal.h"

#include <QObject>
#include <QList>

class QProjectHost;

enum enProjectStatus
{
    PS_CLOSED,
    PS_OPENING,
    PS_OPENED,
    PS_BOTTOM
};

class QAbstractWidgetHost;

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

    void        addForm(QAbstractWidgetHost* host,int index = -1);
protected:
    void        setProjectStatus(enProjectStatus newStatus);
signals:
    void        projectOpened();
    void        projectClosed();

    void        projectStatusChanged(enProjectStatus newStatus);

    void        hostAdded(QAbstractWidgetHost* host,int index);
protected:
    QProjectHost    *m_projectHost;

    enProjectStatus m_projectStatus;

    QList<QAbstractWidgetHost*>     m_forms;
};

#endif // QPROJECT_H
