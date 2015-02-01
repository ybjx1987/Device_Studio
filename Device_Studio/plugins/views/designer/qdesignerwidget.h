#ifndef QDESIGNERWIDGET_H
#define QDESIGNERWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

class QPropertyListView;
class StyledBar;
class QWidgetBoxList;

class QDesignerWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QDesignerWidget(QWidget* parent = 0);

protected:
    QPropertyListView       *m_propertyView;
    StyledBar               *m_propertyViewBar;

    QWidgetBoxList          *m_widgetBoxList;
    StyledBar               *m_widgetBoxListBar;
};

#endif // QDESIGNERWIDGET_H
