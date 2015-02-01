#include "qdesignerplugin.h"

#include "qdesignerwidget.h"

#include <qplugin.h>
#include <QIcon>
#include <QVariant>

void QDesignerPlugin::createWidget()
{
    m_widget = new QDesignerWidget;
    m_widget->setProperty("panelwidget",true);
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
