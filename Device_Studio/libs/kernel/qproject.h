#ifndef QPROJECT_H
#define QPROJECT_H

#include "kernellibglobal.h"

#include <QObject>
#include <QList>

class QLanguageManager;
class QProjectHost;
class QStringProperty;

enum enProjectStatus
{
    PS_CLOSED,
    PS_OPENING,
    PS_OPENED,
    PS_BOTTOM
};

enum enProjectModified
{
    PM_MODIFIED,
    PM_NOT_MODIFIED,
    PM_BOTTOM
};

class QAbstractWidgetHost;
class QAbstractHost;

class KERNEL_EXPORT QProject :public QObject
{
    Q_OBJECT
public:
    QProject();
    ~QProject();

    bool    open(const QString &proFileName);

    void    close();

    QProjectHost * getProjectHost();
    QLanguageManager* getLanguageManager();

    enProjectStatus getProjectStatus();
    enProjectModified getProjectModified();

    void        addForm(QAbstractWidgetHost* host,int index = -1);

    QAbstractHost * getHostByUuid(const QString &uuid);

    QList<QAbstractWidgetHost*> getForms();

    void        setModified(enProjectModified modified);

    bool        save();
protected:
    void        setProjectStatus(enProjectStatus newStatus);
    void        loadPages(const QString &path);
protected slots:
    void        updateStringProperty(QStringProperty *pro);
    void        languageChanged();
signals:
    void        projectOpened();
    void        projectClosed();

    void        projectStatusChanged(enProjectStatus newStatus);
    void        modifiedChanged();

    void        hostAdded(QAbstractWidgetHost* host,int index);
protected:
    QProjectHost    *m_projectHost;

    enProjectStatus m_projectStatus;

    QList<QAbstractWidgetHost*>     m_forms;
    enProjectModified   m_projectModified;

    QLanguageManager                *m_languageManager;
};

#endif // QPROJECT_H
