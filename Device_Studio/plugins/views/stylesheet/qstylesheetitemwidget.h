#ifndef QSTYLESHEETITEMWIDGET_H
#define QSTYLESHEETITEMWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

class QTitleWidget;
class QItemEndWidget;
class QItemPropertyListView;

class QStyleSheetItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QStyleSheetItemWidget(QWidget *parent = 0);
    ~QStyleSheetItemWidget();

protected:
    void    updateHeight();
signals:

public slots:
protected:
    QTitleWidget        *m_titleWidget;
    QItemEndWidget      *m_endWidget;
    QItemPropertyListView   *m_propertyListView;
    QVBoxLayout         *m_layout;
};

#endif // QSTYLESHEETITEMWIDGET_H
