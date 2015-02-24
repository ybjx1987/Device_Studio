#ifndef QDATAWIDGET_H
#define QDATAWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

class QPropertyListView;
class StyledBar;
class QDataListView;

class QDataWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QDataWidget(QWidget * parent = NULL);
protected:
    QDataListView       *m_dataListview;
    StyledBar           *m_dataListviewBar;

    QPropertyListView   *m_dataPropertyView;
    StyledBar           *m_dataPropertyViewBar;
};

#endif // QDATAWIDGET_H
