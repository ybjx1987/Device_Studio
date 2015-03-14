#include "qsoftcore.h"

#include "../kernel/qproject.h"
#include "qsoftactionmap.h"
#include "../kernel/host/qprojecthost.h"
#include "qsystemresourcemanager.h"

#include <QDir>
#include <QFile>

QSoftCore* QSoftCore::m_instance = NULL;

QSoftCore::QSoftCore(QObject *parent) :
    QObject(parent),
    m_project(new QProject("Design")),
    m_systemResourceManager(new QSystemResourceManager(this))
{
    initAction();
}

QSoftCore::~QSoftCore()
{
    delete m_project;
    delete m_systemResourceManager;
}

QSoftCore* QSoftCore::getInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new QSoftCore();
    }
    return m_instance;
}

void QSoftCore::releaseInstance()
{
    if(m_instance != NULL)
    {
        delete m_instance;
        m_instance = NULL;
    }
}

void QSoftCore::initAction()
{
    QAction *ac;
    ac=new QAction(QIcon(":/inner/images/fileopen.png"),tr("Open Project"),NULL);
    QSoftActionMap::insertAction("project.open",ac);
    ac=new QAction(QIcon(":/inner/images/filesave.png"),tr("Save Project"),NULL);
    QSoftActionMap::insertAction("project.save",ac);
    ac=new QAction(QIcon(":/inner/images/filenew.png"),tr("New Project"),NULL);
    QSoftActionMap::insertAction("project.new",ac);
    ac=new QAction(QIcon(":/inner/images/close.png"),tr("Close Project"),NULL);
    QSoftActionMap::insertAction("project.close",ac);
}

QProject* QSoftCore::getProject()
{
    return m_project;
}

bool QSoftCore::newProject(const QString &path,const QString &name)
{
    QDir dir;
    dir.mkdir(path+"/"+name);

    clearPath(path+"/"+name);

    copyFile(":/inner/files/project/project.pfl",path+"/"+name+"/project.pfl");

    dir.mkdir(path+"/"+name+"/pages");
    dir.mkdir(path+"/"+name+"/languages");

    copyFile(":/inner/files/project/pages/form.pg",path+"/"+name+"/pages/form.pg");
    copyFile(":/inner/files/project/pages/page.list",path+"/"+name+"/pages/page.list");
    copyFile(":/inner/files/project/languages/language.xml",
             path+"/"+name+"/languages/language.xml");
    copyFile(":/inner/files/project/languages/zh-CN.xml",
             path+"/"+name+"/languages/zh-CN.xml");
    copyFile(":/inner/files/project/languages/EN.xml",
             path+"/"+name+"/languages/EN.xml");
    if(m_project->open(path + "/" + name + "/project.pfl"))
    {
        m_project->getProjectHost()->setPropertyValue("objectName",name);
        saveProject();
        return true;
    }
    else
    {
        return false;
    }
}

void QSoftCore::copyFile(const QString &src, const QString des)
{
    QFile f(src);
    if(!f.exists())
    {
        return;
    }
    QFile lf(des);
    if(!lf.open(QFile::ReadWrite))
    {
        return;
    }

    if(!f.open(QFile::ReadOnly))
    {
        return;
    }

    QString buffer = f.readAll();

    lf.write(buffer.toLocal8Bit());

    lf.close();
    f.close();
}

bool QSoftCore::saveProject()
{
    return m_project->save();
}

void QSoftCore::clearPath(const QString &path)
{
    clearPath(path);

    QDir dir(path);

    QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDot | QDir::NoDotDot);
    while(list.size()>0)
    {
        QFileInfo info = list.takeFirst();
        if(info.isFile())
        {
            QFile f(info.filePath());
            f.remove();
        }
        else
        {
            QString str = info.filePath();
            clearPath(str);
            QDir dir(info.filePath());
            dir.rmdir(info.filePath());
        }
    }
}

QSystemResourceManager * QSoftCore::getSystemResourceManager()
{
    return m_systemResourceManager;
}
