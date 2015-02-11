#ifndef QDESIGNERWIDGET_H
#define QDESIGNERWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

class QPropertyListView;
class StyledBar;
class QWidgetBoxList;
class QFormEditor;
class QAbstractWidgetHost;

class QDesignerWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QDesignerWidget(QWidget* parent = 0);
protected slots:
    void    formAdded(QAbstractWidgetHost* host,int index);
protected:
    QPropertyListView       *m_propertyView;
    StyledBar               *m_propertyViewBar;

    QWidgetBoxList          *m_widgetBoxList;
    StyledBar               *m_widgetBoxListBar;

    QFormEditor             *m_formEditor;
    StyledBar               *m_formEditorBar;
};

#endif // QDESIGNERWIDGET_H
