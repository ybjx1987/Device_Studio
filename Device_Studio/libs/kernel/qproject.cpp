#include "qproject.h"

#include "../kernel/xmlnode.h"

#include <QFile>

QProject::QProject():
    QObject(NULL)
{

}

QProject::~QProject()
{

}

bool QProject::open(const QString &proFileName)
{
    close();
}

void QProject::close()
{

}
