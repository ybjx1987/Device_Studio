#ifndef QPROJECTWIDGET_H
#define QPROJECTWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

class StyledBar;
class QStyleSheetGroupListView;

class QStyleSheetWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QStyleSheetWidget(QWidget * parent = NULL);
protected:
    void    initAction();
protected slots:
    void    projectOpened();
    void    projectClosed();

    void    newGroup();
    void    delGroup();
public slots:
    void    updateAction();
protected:
    QStyleSheetGroupListView    *m_groupView;
    StyledBar                   *m_groupViewBar;
};

#endif // QPROJECTWIDGET_H
