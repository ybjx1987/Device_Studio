#include "qdataplugin.h"

#include "qdatawidget.h"

#include <qplugin.h>
#include <QIcon>
#include <QVariant>

void QDataPlugin::createWidget()
{
    m_widget = new QDataWidget;
    m_widget->setProperty("panelwidget",true);
}

QString QDataPlugin::getPluginName()
{
    return "Plugin.Page.Data";
}

QString QDataPlugin::getPageText()
{
    return tr("Data");
}

QIcon QDataPlugin::getPageIcon()
{
    return QIcon(":/inner/images/data.png");
}

float QDataPlugin::getPageIndex()
{
    return 4;
}

bool QDataPlugin::getPageDefaultEnalbed()
{
    return true;
}
