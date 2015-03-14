#ifndef QRESOURCEWIDGET_H
#define QRESOURCEWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

class StyledBar;
class QResourceListView;

class QResourceWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QResourceWidget(QWidget * parent = NULL);
protected slots:
    void    projectOpened();
    void    projectClosed();
protected:
    void    registerAction();
    void    updateAction();
protected:

    StyledBar   *m_resourceListViewBar;
    QResourceListView   *m_resourceListView;
};

#endif // QRESOURCEWIDGET_H
