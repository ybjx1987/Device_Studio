#ifndef QRESOURCEFILE_H
#define QRESOURCEFILE_H

#include <QObject>
#include <QIcon>

class XmlNode;

class QResourceFile : public QObject
{
    Q_OBJECT
public:
    explicit QResourceFile(const QString & path,const QString & filePath);
    ~QResourceFile();

    QIcon   getIcon();

    QString getName();
    QString getPath();
    QString getUuid();
    QByteArray  getData();
    uchar*      getRccData();

    void    setName(const QString & name);

    void    toXml(XmlNode * xml);
    void    fromXml(XmlNode * xml);
signals:
                void    nameChanged();
protected:
    QString     m_name;
    QString     m_path;
    QString     m_uuid;
    QByteArray  m_data;
    uchar       *m_rccData;
};

#endif // QRESOURCEFILE_H
