#include "qsoftcore.h"

#include "../kernel/qproject.h"
#include "qsoftactionmap.h"

#include <QDir>
#include <QFile>

QSoftCore* QSoftCore::m_instance = NULL;

QSoftCore::QSoftCore(QObject *parent) :
    QObject(parent),
    m_project(new QProject)
{
    initAction();
}

QSoftCore::~QSoftCore()
{
    delete m_project;
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

    QFile f(":/inner/files/project/project.pfl");
    QFile lf(path+"/"+name+"/project.pfl");
    if(!lf.open(QFile::ReadWrite))
    {
        return false;
    }

    lf.write(f.readAll());

    return true;
}
