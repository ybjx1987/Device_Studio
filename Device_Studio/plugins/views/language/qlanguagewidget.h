#ifndef QLANGUAGEWIDGET_H
#define QLANGUAGEWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

class StyledBar;


class QLanguageWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QLanguageWidget(QWidget* parent = NULL);

protected:
    StyledBar       *m_languageBar;
};

#endif // QLANGUAGEWIDGET_H
