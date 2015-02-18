#include "qlanguagemanager.h"

#include "qlanguage.h"

#include "../xmlnode.h"

#include <QFile>

QLanguageManager::QLanguageManager(QObject *parent) : QObject(parent)
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
    m_uuidToLanguage.clear();
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

   QLanguage *language = new QLanguage("",this);

   if(!language->load(fileName))
   {
       delete language;
       return;
   }
   else
   {
       m_languages.append(language);
   }
}
