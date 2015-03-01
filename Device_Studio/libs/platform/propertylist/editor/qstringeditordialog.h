#ifndef QSTRINGEDITORDIALOG_H
#define QSTRINGEDITORDIALOG_H

#include "../../platformlibglobal.h"

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class QStringEditorDialog;
}

class QLanguage;
class QBaseListView;
class QLanguageManager;
class QStringProperty;
class QCompleter;

class PLATFORM_EXPORT QStringEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QStringEditorDialog(QStringProperty * property,QWidget *parent = 0);
    ~QStringEditorDialog();
private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void keyChanged();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::QStringEditorDialog *ui;
protected:
    QBaseListView       *m_listView;
    QLanguageManager    *m_languageManager;

    QMap<QTreeWidgetItem*,QLanguage*>   m_itemToLanguage;
    QMap<QLanguage*,QTreeWidgetItem*>   m_languageToItem;
    QSize               m_lastSize;
    QStringProperty     *m_property;
    QCompleter          *m_completer;
};

#endif // QSTRINGEDITORDIALOG_H
