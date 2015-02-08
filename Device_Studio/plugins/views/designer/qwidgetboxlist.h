#ifndef QWIDGETBOXLIST_H
#define QWIDGETBOXLIST_H

#include "../../../libs/platform/qbaselistview.h"

class QWidgetHostInfo;

class QWidgetBoxList : public QBaseListView
{
    Q_OBJECT
public:
    QWidgetBoxList(QWidget* parent = 0);

protected:
    void    addWidget(QWidgetHostInfo * info);
    void    initWidgetBox();
protected:
    QMap<QWidgetHostInfo*,QTreeWidgetItem*> m_infoToItem;
    QMap<QTreeWidgetItem*,QWidgetHostInfo*> m_itemToInfo;
    QMap<QString,QTreeWidgetItem*>      m_nameToGroup;
};

#endif // QWIDGETBOXLIST_H
