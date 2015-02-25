#ifndef QDATAGROUP_H
#define QDATAGROUP_H

#include <QObject>

class QAbstractDataHost;
class XmlNode;

class QDataGroup : public QObject
{
    Q_OBJECT
public:
    explicit QDataGroup(QObject *parent = 0);
    ~QDataGroup();

    QString     getGroupName();
    void        setGroupName(const QString & groupName);

    QString     getUuid();

    void        addData(QAbstractDataHost * data,int index = -1);
    void        delData(QAbstractDataHost * data);

    QAbstractDataHost* getData(const QString & name);
    QList<QAbstractDataHost*> getDatas();
    QAbstractDataHost* getDataByUuid(const QString & uuid);

    bool    save(XmlNode * xml);
    bool    load(XmlNode * xml);

signals:
    void    groupNameChanged();
    void    dataAdded(QAbstractDataHost * data, int index);
    void    dataDeled(QAbstractDataHost * data);
protected:
    QString     m_groupName;
    QString     m_uuid;
    QList<QAbstractDataHost*>   m_datas;
};

#endif // QDATAGROUP_H
