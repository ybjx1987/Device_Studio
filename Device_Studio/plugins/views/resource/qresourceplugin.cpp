#include "qresourceplugin.h"

#include "qresourcewidget.h"
#include "editor/qeditorfactory.h"

#include <qplugin.h>
#include <QIcon>
#include <QVariant>

void QResourcePlugin::createWidget()
{
    QEditorFactory::registerInnerEditor();
    m_widget = new QResourceWidget;
    m_widget->setProperty("panelwidget",true);
}

QString QResourcePlugin::getPluginName()
{
    return "Plugin.Page.Resource";
}

QString QResourcePlugin::getPageText()
{
    return tr("Resource");
}

QIcon QResourcePlugin::getPageIcon()
{
    return QIcon(":/inner/images/resource.png");
}

float QResourcePlugin::getPageIndex()
{
    return 6;
}

bool QResourcePlugin::getPageDefaultEnalbed()
{
    return false;
}
