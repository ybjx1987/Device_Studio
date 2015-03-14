#include "qresourcefile.h"

#include "../xmlnode.h"
#include "qrccfilemaker.h"

#include <QUuid>
#include <QFile>

QResourceFile::QResourceFile(const QString & path,const QString & filePath) :
    QObject(NULL),
    m_path(path)
{
    m_uuid = QUuid::createUuid().toString();
    m_path.replace("\\","/");
    if(m_path.startsWith("/"))
    {
        m_path = m_path.mid(1);
    }

    QFile f(filePath);
    if(f.exists())
    {
        if(f.open(QFile::ReadOnly))
        {
            m_data = f.readAll();
        }
    }

    QRccFileMaker maker;
    maker.setResourceFile(this);
    QByteArray rccData =maker.rccData();
    m_rccData = new uchar[rccData.size()];
    memcpy(m_rccData,rccData.data(),rccData.size());
}

QResourceFile::~QResourceFile()
{
    delete m_rccData;
}

QString QResourceFile::getName()
{
    return m_name;
}

void QResourceFile::setName(const QString &name)
{
    if(m_name != name)
    {
        m_name = name;
        emit nameChanged();
    }
}

QIcon QResourceFile::getIcon()
{
    return QIcon();
}

QString QResourceFile::getPath()
{
    return m_path;
}

QString QResourceFile::getUuid()
{
    return m_uuid;
}

void QResourceFile::fromXml(XmlNode *xml)
{
    m_uuid = xml->getProperty("uuid");
    if(m_uuid == "")
    {
        m_uuid = QUuid::createUuid().toString();
    }
    m_name = xml->getProperty("name");
    m_path = xml->getProperty("path");
}

void QResourceFile::toXml(XmlNode *xml)
{
    xml->setTitle("Resource");
    xml->setProperty("uuid",m_uuid);
    xml->setProperty("name",m_name);
    xml->setProperty("path",m_path);
}

QByteArray QResourceFile::getData()
{
    return m_data;
}

uchar * QResourceFile::getRccData()
{
    return m_rccData;
}
