#ifndef QSTYLESHEETWIDGET_H
#define QSTYLESHEETWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

#include <QWidget>
#include <QStackedWidget>
#include <QMap>

class QStyleSheetGroup;
class QStyleSheetGroupListView;
class StyledBar;
class QOneGroupWidget;

class QStyleSheetWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    explicit QStyleSheetWidget(QWidget *parent = 0);
    ~QStyleSheetWidget();

signals:

protected:
    void    projectOpened();
    void    projectClosed();

    void    addGroup(QStyleSheetGroup * group);

    void    initAction();
    void    updateAction();
protected slots:
    void    groupSelected(QStyleSheetGroup * group);

    void    newGroup();
    void    delGroup();

    void    groupAdded(QStyleSheetGroup * group);
    void    groupDeled(QStyleSheetGroup * group);
protected:
    QStyleSheetGroupListView    *m_groupListView;
    StyledBar                   *m_groupListViewBar;
    QStackedWidget              *m_itemWidget;
    StyledBar                   *m_itemWidgetBar;

    QMap<QStyleSheetGroup*,QOneGroupWidget*>    m_groupToWidget;
    QMap<QOneGroupWidget*,QStyleSheetGroup*>    m_widgetToGroup;
};

#endif // QSTYLESHEETWIDGET_H
