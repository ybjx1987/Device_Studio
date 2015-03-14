#ifndef QSOFTCORE_H
#define QSOFTCORE_H

#include "platformlibglobal.h"

#include <QObject>

class QProject;
class QSystemResourceManager;

class PLATFORM_EXPORT QSoftCore : public QObject
{
    Q_OBJECT
protected:
    explicit QSoftCore(QObject *parent = 0);
public:
    ~QSoftCore();

    static QSoftCore*  getInstance();
    static void        releaseInstance();



public:
    QProject*   getProject();
    QSystemResourceManager  *getSystemResourceManager();

    bool        newProject(const QString & path, const QString & name);
    bool        saveProject();
protected:
    void        clearPath(const QString &path);
    void        initAction();
    void        copyFile(const QString &src,const QString des);
signals:

public slots:

protected:
    static      QSoftCore*      m_instance;
    QProject    *m_project;
    QSystemResourceManager  *m_systemResourceManager;
};

#endif // QSOFTCORE_H
