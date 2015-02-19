#ifndef QLANGUAGE_H
#define QLANGUAGE_H

#include <QObject>
#include <QStringList>
#include <QMap>

class QLanguage : public QObject
{
    Q_OBJECT
public:
    explicit QLanguage(const QString &id="",QObject *parent = 0);
    ~QLanguage();

    bool    load(const QString &fileName);

    QString getID();

    void    addItem(const QString &key,const QString &value);
    void    delItem(const QString &key);

    QStringList  getKeys();
    QString      getValue(const QString &key);
signals:
    void  itemAdded(const QString &key);
    void  itemDeled(const QString &key);
protected:
    QString m_id;

    QStringList     m_keys;
    QMap<QString,QString>   m_keyToValue;
};

#endif // QLANGUAGE_H
