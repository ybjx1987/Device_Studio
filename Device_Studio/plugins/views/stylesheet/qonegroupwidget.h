#ifndef QONEGROUPWIDGET_H
#define QONEGROUPWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMap>

class QStyleSheetGroup;
class QStyleSheetItemWidget;
class QStyleSheetItem;

class QOneGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QOneGroupWidget(QStyleSheetGroup * group,QWidget *parent = 0);
    ~QOneGroupWidget();

    void clear();
signals:

protected slots:
    void    itemAdded(QStyleSheetItem * item);
    void    itemDeled(QStyleSheetItem * item);

    void    delItem();
protected slots:

    void    updateRect();
protected:
    QStyleSheetGroup    *m_group;
    QMap<QStyleSheetItem*,QStyleSheetItemWidget*> m_itemToWidget;
    QVBoxLayout     *m_layout;
};

#endif // QONEGROUPWIDGET_H
