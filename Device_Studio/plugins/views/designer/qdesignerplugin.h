#ifndef QDESIGNERPLUGIN_H
#define QDESIGNERPLUGIN_H

#include "../../../libs/platform/qabstractpage.h"

class QDesignerPlugin : public QAbstractPage
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugin.page.designer" FILE "designer.json")
public:
    QString     getPluginName();
    QString     getPageText();
    QIcon       getPageIcon();
    float       getPageIndex();
    bool        getPageDefaultEnalbed();
protected:
    void        createWidget();
};

#endif // QDESIGNERPLUGIN_H
