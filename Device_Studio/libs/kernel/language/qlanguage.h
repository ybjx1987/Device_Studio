#ifndef QLANGUAGE_H
#define QLANGUAGE_H

#include <QObject>
#include <QStringList>
#include <QMap>

class QLanguage : public QObject
{
    Q_OBJECT
public:
    explicit QLanguage(const QString &name="",QObject *parent = 0);
    ~QLanguage();

    bool    load(const QString &fileName);

    QString getName();
    QString getUuid();
signals:

public slots:

protected:
    QString m_name;
    QString m_uuid;

    QStringList     m_keys;
    QMap<QString,QString>   m_keyToValue;
};

#endif // QLANGUAGE_H
