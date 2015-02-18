#ifndef QLANGUAGEMANAGER_H
#define QLANGUAGEMANAGER_H

#include <QObject>
#include <QMap>

class QLanguage;

class QLanguageManager : public QObject
{
    Q_OBJECT
public:
    explicit QLanguageManager(QObject *parent = 0);
    ~QLanguageManager();

    void    load(const QString &path);

protected:
    void    clear();
    void    loadLanguage(const QString &fileName);
signals:

public slots:
protected:
    QList<QLanguage*>           m_languages;
    QMap<QString,QLanguage*>    m_uuidToLanguage;
};

#endif // QLANGUAGEMANAGER_H
