#ifndef QONELANGUAGEVIEW_H
#define QONELANGUAGEVIEW_H

#include "../../../libs/platform/qbaselistview.h"

class QLanguage;

class QOneLanguageView : public QBaseListView
{
    Q_OBJECT
public:
    QOneLanguageView(QLanguage * language,QWidget* parent =NULL);
    ~QOneLanguageView();
protected:
    QLanguage   *m_language;
};

#endif // QONELANGUAGEVIEW_H
