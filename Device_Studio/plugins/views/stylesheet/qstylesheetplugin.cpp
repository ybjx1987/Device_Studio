#include "qstylesheetplugin.h"

#include "qstylesheetwidget.h"

#include <qplugin.h>
#include <QIcon>
#include <QVariant>

void QStyleSheetPlugin::createWidget()
{
    m_widget = new QStyleSheetWidget;
    m_widget->setProperty("panelwidget",true);
}

QString QStyleSheetPlugin::getPluginName()
{
    return "Plugin.Page.StyleSheet";
}

QString QStyleSheetPlugin::getPageText()
{
    return tr("Style Sheet");
}

QIcon QStyleSheetPlugin::getPageIcon()
{
    return QIcon(":/inner/images/stylesheet.png");
}

float QStyleSheetPlugin::getPageIndex()
{
    return 5;
}

bool QStyleSheetPlugin::getPageDefaultEnalbed()
{
    return true;
}
