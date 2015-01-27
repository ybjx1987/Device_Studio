#ifndef QPROJECT_H
#define QPROJECT_H

#include <QObject>

class QProjectHost;

class QProject :public QObject
{
    Q_OBJECT
public:
    QProject();
    ~QProject();

    bool    open(const QString &proFileName);

    void    close();

    QProjectHost * getProjectHost();
protected:
    QProjectHost    *m_projectHost;
};

#endif // QPROJECT_H
