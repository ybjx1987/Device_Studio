#ifndef QSTYLESHEETITEMWIDGET_H
#define QSTYLESHEETITEMWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

class QTitleWidget;
class QItemEndWidget;
class QItemPropertyListView;
class QStyleSheetItem;
class QStyleSheetItemTitle;

class QStyleSheetItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QStyleSheetItemWidget(QStyleSheetItem * item,QWidget *parent = 0);
    ~QStyleSheetItemWidget();

protected:
    void    updateHeight();
signals:

protected slots:
    void    addTitle();
    void    delTitle(const QString &title);

    void    titleAdded(QStyleSheetItemTitle * title);
    void    titleDeled(QStyleSheetItemTitle * title);
protected:
    QTitleWidget        *m_titleWidget;
    QItemEndWidget      *m_endWidget;
    QItemPropertyListView   *m_propertyListView;
    QVBoxLayout         *m_layout;
    QStyleSheetItem     *m_sheetItem;
};

#endif // QSTYLESHEETITEMWIDGET_H
