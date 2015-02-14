#include "qprojectplugin.h"

#include "qprojectwidget.h"

#include <qplugin.h>
#include <QIcon>
#include <QVariant>

void QProjectPlugin::createWidget()
{
    m_widget = new QProjectWidget;
    m_widget->setProperty("panelwidget",true);
}

QString QProjectPlugin::getPluginName()
{
    return "Plugin.Page.Project";
}

QString QProjectPlugin::getPageText()
{
    return tr("Project");
}

QIcon QProjectPlugin::getPageIcon()
{
    return QIcon(":/inner/images/project.png");
}

float QProjectPlugin::getPageIndex()
{
    return 1;
}

bool QProjectPlugin::getPageDefaultEnalbed()
{
    return true;
}
