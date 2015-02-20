#ifndef QPROJECTPLUGIN_H
#define QPROJECTPLUGIN_H


#include "../../../libs/platform/qabstractpage.h"

class QLanguagePlugin : public QAbstractPage
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugin.page.language" FILE "language.json")
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
