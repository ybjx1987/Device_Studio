#include "qlanguagemanager.h"

#include "qlanguage.h"

#include "../xmlnode.h"

#include <QFile>
#include <QUuid>

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
        else if(obj->getTitle() == "Item")
        {
            QLanguageItem *item = new QLanguageItem;
            item->m_name = obj->getProperty("name");
            item->m_uuid = obj->getProperty("uuid");
            if(item->m_name != "" && item->m_uuid != "")
            {
                m_languageItems.append(item);
                m_uuidToItems.insert(item->m_uuid,item);
                m_nameToItems.insert(item->m_name,item);
            }
            else
            {
                delete item;
            }
        }
    }
}

void QLanguageManager::save(const QString &path)
{
    XmlNode xml;

    xml.setTitle("Languages");

    foreach(QLanguage * language, m_languages)
    {
        XmlNode *obj = new XmlNode(&xml);
        obj->setTitle("Language");
        obj->setText(language->getID()+".xml");
        language->save(path+"/"+language->getID()+".xml");
    }

    foreach(QLanguageItem * item,m_languageItems)
    {
        XmlNode * obj = new XmlNode(&xml);
        obj->setTitle("Item");
        obj->setProperty("name",item->m_name);
        obj->setProperty("uuid",item->m_uuid);
    }

    QString str;
    xml.save(str);
    QFile f(path+"/language.xml");

    if(f.open(QFile::ReadWrite))
    {
        f.write(str.toLocal8Bit());
        f.close();
    }
}

void QLanguageManager::loadLanguage(const QString &fileName)
{

   QLanguage *language = new QLanguage(this);
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

    language = new QLanguage(this,id);

    foreach(QLanguageItem * item,m_languageItems)
    {
        language->addItem(item->m_uuid,item->m_name);
        language->setValue(item->m_uuid,item->m_name);
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

    emit languageDel(language);

    m_languages.removeAll(language);
    m_idToLanguage.remove(language->getID());
    delete language;
}

QLanguage* QLanguageManager::getLanguage(const QString &id)
{
    return m_idToLanguage.value(id);
}

void QLanguageManager::addItem(const QString &name)
{
    if(m_nameToItems.keys().contains(name))
    {
        return;
    }
    QLanguageItem *item = new QLanguageItem;
    item->m_name = name;
    item->m_uuid = QUuid::createUuid().toString();
    m_languageItems.append(item);
    m_nameToItems.insert(item->m_name,item);
    m_uuidToItems.insert(item->m_uuid,item);
    foreach(QLanguage* language,m_languages)
    {
        language->addItem(item->m_uuid,item->m_name);
    }

    emit itemAdded(item);
}

void QLanguageManager::delItem(const QString &uuid)
{
    QLanguageItem * item = m_uuidToItems.value(uuid);
    if(item == NULL)
    {
        return;
    }

    emit itemDeled(item);
    m_languageItems.removeAll(item);
    m_nameToItems.remove(item->m_name);
    m_uuidToItems.remove(item->m_uuid);
    foreach(QLanguage * language,m_languages)
    {
        language->delItem(item->m_uuid);
    }

    delete item;
}

QStringList QLanguageManager::getAllUuids()
{
    return m_uuidToItems.keys();
}

QStringList QLanguageManager::getAllNames()
{
    return m_nameToItems.keys();
}

QLanguageItem * QLanguageManager::getItem(const QString &uuid)
{
    return m_uuidToItems.value(uuid);
}
