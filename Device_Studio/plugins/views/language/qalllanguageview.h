#ifndef QALLLANGUAGEVIEW_H
#define QALLLANGUAGEVIEW_H

#include "../../../libs/platform/qbaselistview.h"

class QLanguageManager;

class QAllLanguageView : public QBaseListView
{
    Q_OBJECT
public:
    QAllLanguageView(QLanguageManager* manager,QWidget * parent = NULL);
    ~QAllLanguageView();

protected:
    QLanguageManager    *m_languageManager;
};

#endif // QALLLANGUAGEVIEW_H
