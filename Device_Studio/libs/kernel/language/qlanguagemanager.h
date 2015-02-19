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

    QList<QLanguage*>   getLanguages();
    QLanguage *         getLanguage(const QString &id);

    QString addLanguage(const QString &id);
    void    removeLanguage(QLanguage * language);
protected:
    void    clear();
    void    loadLanguage(const QString &fileName);
signals:
    void    languageAdd(const QString &id);
    void    languageDel(QLanguage * language);
public slots:
protected:
    QList<QLanguage*>           m_languages;
    QMap<QString,QLanguage*>    m_idToLanguage;
};

#endif // QLANGUAGEMANAGER_H
