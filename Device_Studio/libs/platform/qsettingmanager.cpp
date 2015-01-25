#include "qsettingmanager.h"

#include "../kernel/xmlnode.h"

#include <QFile>
#include <QApplication>

void QSettingManager::setValue(const QString &name, const QVariant &value)
{
    m_settings.insert(name,value);
}

QVariant QSettingManager::getValue(const QString &name, const QVariant &def)
{
    return m_settings.value(name,def);
}

void QSettingManager::save()
{
    QMap<QString,XmlNode*> objs;

    XmlNode xml;
    xml.setTitle("Settings");

    QMapIterator<QString,QVariant> it(m_settings);

    while(it.hasNext())
    {
        it.next();

        int index=it.key().indexOf(".");
        if(index>0)
        {
            XmlNode *obj=objs.value(it.key().left(index));
            if(obj==NULL)
            {
                obj=new XmlNode(&xml);
                obj->setTitle("Group");
                obj->setProperty("name",it.key().left(index));
            }
            XmlNode* o=new XmlNode(obj);
            o->setTitle("Item");
            o->setProperty("name",it.key().mid(index+1));
            o->setProperty("value",variantToString(it.value()));
        }
    }

    QString buff;
    xml.save(buff);

    QFile f(qApp->applicationDirPath()+"/config.xml");

    if(!f.open(QFile::WriteOnly))
    {
        return;
    }
    f.resize(0);
    f.write(buff.toLocal8Bit());
    f.close();
}

void QSettingManager::load()
{
    m_settings.clear();
    QFile f(qApp->applicationDirPath()+"/config.xml");

    if(!f.open(QFile::ReadOnly))
    {
        return;
    }
    QString buffer=f.readAll();

    f.close();

    XmlNode xml;
    if(!xml.load(buffer))
    {
        return;
    }

    if(xml.getTitle()!="Settings")
    {
        return;
    }

    QList<XmlNode*> list=xml.getChildren();

    QString group;
    QString name;
    foreach(XmlNode* o,list)
    {
        group=o->getProperty("name");
        if(group=="")
        {
            continue;
        }
        foreach(XmlNode* c,o->getChildren())
        {
            name=c->getProperty("name");
            if(name=="")
            {
                continue;
            }
            setValue(group+"."+name,stringToVariant(c->getProperty("value")));
        }
    }
}

QString QSettingManager::variantToString(const QVariant &v)
{
    QString result;

    if(v.type()==QVariant::ByteArray)
    {
        result+=QLatin1String("@ByteArray(");

        QString str;
        escapedString(v.toByteArray(),str);
        result+=str;

        result+=QLatin1Char(')');
    }
    else
    {
        result=v.toString();
    }

    return result;
}


QVariant QSettingManager::stringToVariant(const QString &s)
{
    if (s.startsWith(QLatin1String("@ByteArray(")) && s.endsWith(QLatin1Char(')')))
    {
        QByteArray array;
        unescapedString(s.mid(11,s.size()-12),array);
        return array;
    }
    else
    {
        return s;
    }
}

void QSettingManager::escapedString(const QByteArray &array, QString &result)
{
    int count=array.size();


    QString temp;

    for(int i=0;i<count;i++)
    {
        result+="\\";
        result+=temp.sprintf("%X",array.at(i)&0xff);
    }
}

void QSettingManager::unescapedString(const QString &value, QByteArray &result)
{
    QStringList list=QString(value).split("\\");
    list.removeAll("");
    foreach(const QString &s,list)
    {
        result+=char(s.toInt(0,16)&0xff);
    }
}
