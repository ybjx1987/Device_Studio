#ifndef QDESIGNERWIDGET_H
#define QDESIGNERWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

class QPropertyListView;
class StyledBar;
class QWidgetBoxList;
class QFormEditor;
class QAbstractWidgetHost;
class QComboBox;
class QHostListView;

class QDesignerWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QDesignerWidget(QWidget* parent = 0);
protected slots:
    void    formAdded(QAbstractWidgetHost* host,int index);
    void    projectOpened();
    void    projectClosed();

    void    hostSelect(QAbstractWidgetHost* host);
    void    formSelect(QAbstractWidgetHost* host);

    void    selectLanguage();
protected:
    void    initDesignerViewAction();
protected:
    QPropertyListView       *m_propertyView;
    StyledBar               *m_propertyViewBar;

    QWidgetBoxList          *m_widgetBoxList;
    StyledBar               *m_widgetBoxListBar;

    QFormEditor             *m_formEditor;
    StyledBar               *m_formEditorBar;

    QHostListView           *m_hostListView;
    StyledBar               *m_hostListViewBar;

    QComboBox               *m_formlist;

    QAbstractWidgetHost     *m_currentHost;
    QComboBox               *m_languageList;
};

#endif // QDESIGNERWIDGET_H
