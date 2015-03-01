#ifndef QSTYLESHEETGROUPLISTVIEW_H
#define QSTYLESHEETGROUPLISTVIEW_H

#include "../../../libs/platform/qbaselistview.h"

#include <QMap>

class QStyleSheetManager;
class QStyleSheetGroup;

class QStyleSheetGroupListView : public QBaseListView
{
    Q_OBJECT
public:
    QStyleSheetGroupListView(QWidget * parent = NULL);

    void    init(QStyleSheetManager * manager);

    void    clear();
protected slots:
    void    select();
    void    groupAdded(QStyleSheetGroup * group);
    void    groupDeled(QStyleSheetGroup * group);
signals:
    void    groupSelect(QStyleSheetGroup* group);
    void    updateAction();
protected:
    QMap<QStyleSheetGroup*,QTreeWidgetItem*>    m_groupToItem;
    QMap<QTreeWidgetItem*,QStyleSheetGroup*>    m_itemToGroup;
};

#endif // QSTYLESHEETGROUPLISTVIEW_H
