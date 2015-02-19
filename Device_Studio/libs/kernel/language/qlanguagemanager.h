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

    void    addItem(const QString &key,const QString &value);
    void    delItem(const QString &key);

    QStringList getAllKeyword();
protected:
    void    clear();
    void    loadLanguage(const QString &fileName);
signals:
    void    languageAdd(const QString &id);
    void    languageDel(QLanguage * language);

    void    updateItem(const QString &id,const QString &item);
    void    itemAdded(const QString &item);
    void    itemDeled(const QString &item);
protected slots:
    void    languageItemAdded(const QString &key);
    void    languageItemRemove(const QString &key);
protected:
    QList<QLanguage*>           m_languages;
    QMap<QString,QLanguage*>    m_idToLanguage;

    QMap<QString,int>           m_allKeys;
};

#endif // QLANGUAGEMANAGER_H
