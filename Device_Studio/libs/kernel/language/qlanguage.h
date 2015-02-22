#ifndef QLANGUAGE_H
#define QLANGUAGE_H

#include <QObject>
#include <QStringList>
#include <QMap>

class QLanguageManager;

class QLanguage : public QObject
{
    Q_OBJECT
public:
    explicit QLanguage(QLanguageManager * manager,const QString &id="",QObject *parent = 0);
    ~QLanguage();


    QString getID();
    void    addItem(const QString &uuid,const QString &value);
    void    delItem(const QString &uuid);

    QStringList getUuids();
    QString     getValue(const QString &uuid);
    void        setValue(const QString &uuid,const QString &value);

    bool        load(const QString &fileName);
    bool        save(const QString &fileName);

    QLanguageManager    *getManager();
signals:
    void  itemAdded(const QString &key);
    void  itemDeled(const QString &key);
    void  itemUpdated(const QString &key);
protected:
    QString m_id;

    QStringList     m_uuids;
    QMap<QString,QString>   m_uuidToValue;
    QLanguageManager *m_languageManager;
};

#endif // QLANGUAGE_H
