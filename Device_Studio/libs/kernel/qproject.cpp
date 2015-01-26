#include "qproject.h"

#include "host/qprojecthost.h"

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

    QFile f(proFileName);
    if(!f.open(QFile::ReadOnly))
    {
        return false;
    }

    QString buffer = f.readAll();
    f.close();

    XmlNode xml;

    if(!xml.load(buffer))
    {
        return false;
    }

    m_projectHost = new QProjectHost;

    return true;
}

void QProject::close()
{

}
