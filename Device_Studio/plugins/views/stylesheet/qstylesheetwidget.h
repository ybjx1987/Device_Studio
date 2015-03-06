#ifndef QSTYLESHEETWIDGET_H
#define QSTYLESHEETWIDGET_H

#include <QWidget>
#include <QStackedWidget>

class QStyleSheetGroupListView;
class StyledBar;

class QStyleSheetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QStyleSheetWidget(QWidget *parent = 0);
    ~QStyleSheetWidget();

signals:

public slots:
protected:
    QStyleSheetGroupListView    *m_groupListView;
    StyledBar                   *m_groupListViewBar;
    QStackedWidget              *m_itemWidget;
    StyledBar                   *m_itemWidgetBar;
};

#endif // QSTYLESHEETWIDGET_H
