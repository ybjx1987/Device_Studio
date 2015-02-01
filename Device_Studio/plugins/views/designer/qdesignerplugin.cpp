#include "qdesignerplugin.h"

#include <qplugin.h>
#include <QIcon>
#include <QVariant>

void QDesignerPlugin::createWidget()
{
    m_widget = NULL;
}

QString QDesignerPlugin::getPluginName()
{
    return "Plugin.Page.Designer";
}

QString QDesignerPlugin::getPageText()
{
    return tr("Designer");
}

QIcon QDesignerPlugin::getPageIcon()
{
    return QIcon(":/inner/images/design.png");
}

float QDesignerPlugin::getPageIndex()
{
    return 2;
}

bool QDesignerPlugin::getPageDefaultEnalbed()
{
    return true;
}
