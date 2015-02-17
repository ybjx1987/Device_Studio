#include "qlanguageplugin.h"

#include "qlanguagewidget.h"

#include <qplugin.h>
#include <QIcon>
#include <QVariant>

void QLanguagePlugin::createWidget()
{
    m_widget = new QLanguageWidget;
    m_widget->setProperty("panelwidget",true);
}

QString QLanguagePlugin::getPluginName()
{
    return "Plugin.Page.Language";
}

QString QLanguagePlugin::getPageText()
{
    return tr("Language");
}

QIcon QLanguagePlugin::getPageIcon()
{
    return QIcon(":/inner/images/language.png");
}

float QLanguagePlugin::getPageIndex()
{
    return 3;
}

bool QLanguagePlugin::getPageDefaultEnalbed()
{
    return true;
}
