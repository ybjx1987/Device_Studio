#ifndef QDATAWIDGET_H
#define QDATAWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

class QPropertyListView;
class StyledBar;

class QDataWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QDataWidget(QWidget * parent = NULL);
};

#endif // QDATAWIDGET_H
