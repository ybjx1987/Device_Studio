#ifndef QLANGUAGEMANAGER_H
#define QLANGUAGEMANAGER_H

#include <QObject>
#include <QMap>

class QLanguage;

class QLanguageItem
{
public:
    QString     m_uuid;
    QString     m_name;
};

class QLanguageManager : public QObject
{
    Q_OBJECT
public:
    explicit QLanguageManager(QObject *parent = 0);
    ~QLanguageManager();

    void    load(const QString &path);
    void    save(const QString &path);

    QList<QLanguage*>   getLanguages();
    QLanguage *         getLanguage(const QString &id);

    QString addLanguage(const QString &id);
    void    removeLanguage(QLanguage * language);

    void    addItem(const QString &name);
    void    delItem(const QString &uuid);

    QStringList getAllUuids();
    QStringList getAllNames();

    QLanguageItem*  getItem(const QString &uuid);
    QLanguageItem*  getItemByName(const QString &name);

    void    setCurrentLanguage(const QString &id);
    QLanguage * getCurrentLanguage();
protected:
    void    clear();
    void    loadLanguage(const QString &fileName);
signals:
    void    languageAdd(const QString &id);
    void    languageDel(QLanguage * language);
    void    itemAdded(QLanguageItem * item);
    void    itemDeled(QLanguageItem * item);

    void    currentLanguageChanged(const QString &id);
protected:
    QList<QLanguage*>           m_languages;
    QMap<QString,QLanguage*>    m_idToLanguage;

    QList<QLanguageItem*>       m_languageItems;
    QMap<QString,QLanguageItem*>    m_uuidToItems;
    QMap<QString,QLanguageItem*>    m_nameToItems;
    QString                     m_currentLanguageID;
};

#endif // QLANGUAGEMANAGER_H
