#ifndef QDATAPLUGIN_H
#define QDATAPLUGIN_H

#include "../../../libs/platform/qabstractpage.h"

class QDataPlugin : public QAbstractPage
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugin.page.data" FILE "data.json")
public:
    QString     getPluginName();
    QString     getPageText();
    QIcon       getPageIcon();
    float       getPageIndex();
    bool        getPageDefaultEnalbed();
protected:
    void        createWidget();
};

#endif // QDATAPLUGIN_H
