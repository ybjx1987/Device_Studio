#include "qproject.h"

#include "host/qprojecthost.h"

#include "../kernel/xmlnode.h"

#include <QFile>

QProject::QProject():
    QObject(NULL),
    m_projectHost(NULL)
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
    m_projectHost->init();
    m_projectHost->fromXml(&xml);


    return true;
}

void QProject::close()
{
    if(m_projectHost != NULL)
    {
        delete m_projectHost;
        m_projectHost = NULL;
    }
}

QProjectHost* QProject::getProjectHost()
{
    return m_projectHost;
}
