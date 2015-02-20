#ifndef QLANGUAGEWIDGET_H
#define QLANGUAGEWIDGET_H

#include "../../../libs/platform/qabstractpagewidget.h"

#include <QStackedWidget>
#include <QMap>

class StyledBar;
class QLanguageList;
class QLanguage;

class QLanguageWidget : public QAbstractPageWidget
{
    Q_OBJECT
public:
    QLanguageWidget(QWidget* parent = NULL);
protected slots:
    void    projectOpened();
    void    projectClosed();

    void    languageSelect(const QString &uuid);
protected:
    void    clear();
    void    insertLanguage(QLanguage * language,int index = -1);
    void    initAction();
    void    updateAction();
protected slots:
    void    addLanguage();
    void    languageAdded(const QString &id);

    void    delLanguage();
    void    languageDeled(QLanguage * language);

    void    addItem();

    void    delItem();
protected:
    StyledBar       *m_languageListBar;
    QLanguageList   *m_languageList;
    StyledBar       *m_languageViewBar;
    QStackedWidget  *m_languageView;

    QMap<QString,QWidget*>  m_uuidToQWidget;
    QString         m_selectUuid;
};

#endif // QLANGUAGEWIDGET_H
