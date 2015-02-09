#ifndef QSOFTCORE_H
#define QSOFTCORE_H

#include "platformlibglobal.h"

#include <QObject>

class QProject;

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

    bool        newProject(const QString & path, const QString & name);
protected:
    void        initAction();
signals:

public slots:

protected:
    static      QSoftCore*      m_instance;
    QProject    *m_project;
};

#endif // QSOFTCORE_H
