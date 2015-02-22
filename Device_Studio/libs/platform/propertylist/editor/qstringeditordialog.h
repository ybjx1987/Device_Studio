#ifndef QSTRINGEDITORDIALOG_H
#define QSTRINGEDITORDIALOG_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class QStringEditorDialog;
}

class QLanguage;
class QBaseListView;
class QLanguageManager;

class QStringEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QStringEditorDialog(const QString &uuid,QWidget *parent = 0);
    ~QStringEditorDialog();

    QString  getUuid();

    int      getRet();
private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void keyChanged();

private:
    Ui::QStringEditorDialog *ui;
protected:
    QBaseListView       *m_listView;
    QLanguageManager    *m_languageManager;
    QString             m_uuid;
    int                 m_ret;

    QMap<QTreeWidgetItem*,QLanguage*>   m_itemToLanguage;
    QMap<QLanguage*,QTreeWidgetItem*>   m_languageToItem;
};

#endif // QSTRINGEDITORDIALOG_H
