#ifndef QRESOURCEPLUGIN_H
#define QRESOURCEPLUGIN_H


#include "../../../libs/platform/qabstractpage.h"

class QResourcePlugin : public QAbstractPage
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugin.page.resource" FILE "resource.json")
public:
    QString     getPluginName();
    QString     getPageText();
    QIcon       getPageIcon();
    float       getPageIndex();
    bool        getPageDefaultEnalbed();
protected:
    void        createWidget();
};

#endif // QRESOURCEPLUGIN_H
