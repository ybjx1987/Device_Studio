#ifndef QPROJECTPLUGIN_H
#define QPROJECTPLUGIN_H


#include "../../../libs/platform/qabstractpage.h"

class QStyleSheetPlugin : public QAbstractPage
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugin.page.stylesheet" FILE "stylesheet.json")
public:
    QString     getPluginName();
    QString     getPageText();
    QIcon       getPageIcon();
    float       getPageIndex();
    bool        getPageDefaultEnalbed();
protected:
    void        createWidget();
};

#endif // QPROJECTPLUGIN_H
