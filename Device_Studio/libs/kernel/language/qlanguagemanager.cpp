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

    emit languageDel(language);

    m_languages.removeAll(language);
    m_idToLanguage.remove(language->getID());
    delete language;
}

QLanguage* QLanguageManager::getLanguage(const QString &id)
{
    return m_idToLanguage.value(id);
}
