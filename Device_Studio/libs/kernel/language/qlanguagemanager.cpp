#include "qlanguagemanager.h"

#include "qlanguage.h"

#include "../xmlnode.h"

#include <QFile>

QLanguageManager::QLanguageManager(QObject *parent) :
    QObject(parent)
{

}

QLanguageManager::~QLanguageManager()
{
    clear();
}

void QLanguageManager::clear()
{
    qDeleteAll(m_languages);
    m_languages.clear();
    m_idToLanguage.clear();
}

void QLanguageManager::load(const QString &path)
{
    QFile f(path+"/language.xml");

    if(!f.exists())
    {
        return;
    }

    if(!f.open(QFile::ReadOnly))
    {
        return;
    }

    QString buffer = f.readAll();

    XmlNode xml;
    if(!xml.load(buffer))
    {
        return;
    }


    foreach(XmlNode *obj,xml.getChildren())
    {
        if(obj->getTitle() == "Language")
        {
            loadLanguage(path+"/"+obj->getText());
        }
    }
}

void QLanguageManager::loadLanguage(const QString &fileName)
{

   QLanguage *language = new QLanguage();
    connect(language,SIGNAL(itemAdded(QString)),
            this,SLOT(languageItemAdded(QString)));
    connect(language,SIGNAL(itemDeled(QString)),
            this,SLOT(languageItemRemove(QString)));
   if(!language->load(fileName))
   {
       delete language;
       return;
   }
   else
   {
       m_languages.append(language);
       m_idToLanguage.insert(language->getID(),language);
   }
}

QList<QLanguage*> QLanguageManager::getLanguages()
{
    return m_languages;
}

QString QLanguageManager::addLanguage(const QString &id)
{
    QLanguage* language = m_idToLanguage.value(id);
    if(language != NULL)
    {
        return tr("This language has been added!");
    }

    language = new QLanguage(id);
    connect(language,SIGNAL(itemAdded(QString)),
            this,SLOT(languageItemAdded(QString)));
    connect(language,SIGNAL(itemDeled(QString)),
            this,SLOT(languageItemRemove(QString)));
    if(m_languages.size() !=0)
    {
        QLanguage *temp = m_languages.first();
        QStringList list = temp->getKeys();
        foreach(QString str,list)
        {
            language->addItem(str,"");
        }
    }

    m_languages.append(language);
    m_idToLanguage.insert(id,language);

    emit languageAdd(id);
    return "";
}

void QLanguageManager::removeLanguage(QLanguage *language)
{
    if(!m_languages.contains(language))
    {
        return;
    }

    foreach(QString str,language->getKeys())
    {
        int count = m_allKeys.value(str,0);
        count --;
        if(count <= 0)
        {
            m_allKeys.remove(str);
        }
        else
        {
            m_allKeys.insert(str,count);
        }
    }

    emit languageDel(language);

    m_languages.removeAll(language);
    m_idToLanguage.remove(language->getID());
    delete language;
}

QLanguage* QLanguageManager::getLanguage(const QString &id)
{
    return m_idToLanguage.value(id);
}

void QLanguageManager::addItem(const QString &key, const QString &value)
{
    foreach(QLanguage * language,m_languages)
    {
        language->addItem(key,value);
    }
}

void QLanguageManager::delItem(const QString &key)
{
    foreach(QLanguage * language,m_languages)
    {
        language->delItem(key);
    }
}

void QLanguageManager::languageItemAdded(const QString &key)
{
    int count = m_allKeys.value(key,0);
    count ++;
    m_allKeys.insert(key,count);
    QLanguage * language = (QLanguage*)sender();
    if(count == 1)
    {
        emit itemAdded(key);
    }
    emit updateItem(language->getID(),key);
}

void QLanguageManager::languageItemRemove(const QString &key)
{
    QLanguage * language = (QLanguage*)sender();
    int count = m_allKeys.value(key,0);
    count --;
    if(count == 0)
    {
        m_allKeys.remove(key);
        emit itemDeled(key);
    }
    else
    {
        m_allKeys.insert(key,count);
        emit updateItem(language->getID(),key);
    }
}

QStringList QLanguageManager::getAllKeyword()
{
    return m_allKeys.keys();
}
