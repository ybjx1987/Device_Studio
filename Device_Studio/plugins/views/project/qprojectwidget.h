#ifndef QPROJECTWIDGET_H
#define QPROJECTWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

class QPropertyListView;
class StyledBar;

class QPageView;

class QProjectWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QProjectWidget(QWidget * parent = NULL);
protected slots:
    void    projectOpened();
protected:
    QPropertyListView   *m_projectPropertyView;
    StyledBar           *m_projectBar;

    QPageView           *m_pageView;
    StyledBar           *m_pageViewBar;
};

#endif // QPROJECTWIDGET_H
