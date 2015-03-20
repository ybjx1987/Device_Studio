#ifndef QRESOURCEWIDGET_H
#define QRESOURCEWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

#include <QStackedWidget>
#include <QFile>
#include <QMap>

class StyledBar;
class QResourceListView;
class QResourceFile;
class QAbstractFileEditor;
class QActionToolBar;

class QResourceWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QResourceWidget(QWidget * parent = NULL);
protected slots:
    void    projectOpened();
    void    projectClosed();

    void    resourceSelect(QResourceFile * resource);

    void    addResource();
    void    removeResource();
protected:
    void    registerAction();
    void    updateAction();
protected:

    StyledBar   *m_resourceListViewBar;
    QResourceListView   *m_resourceListView;

    QStackedWidget      *m_editorView;
    StyledBar           *m_editorViewBar;

    QMap<QResourceFile*,QAbstractFileEditor*>   m_resourceToWidget;

    QActionToolBar      *m_editorViewToolBar;
};

#endif // QRESOURCEWIDGET_H
