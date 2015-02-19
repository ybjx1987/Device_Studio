#ifndef QDELLANGUAGEDIALOG_H
#define QDELLANGUAGEDIALOG_H

#include <QDialog>
#include <QTreeWidget>

class QBaseListView;

namespace Ui {
class QDelLanguageDialog;
}

class QLanguage;

class QDelLanguageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDelLanguageDialog(QWidget *parent = 0);
    ~QDelLanguageDialog();

private:
    Ui::QDelLanguageDialog *ui;
protected slots:
    void    clicked(QTreeWidgetItem * item);
protected:
    QBaseListView   *m_listview;
    QMap<QLanguage*,QTreeWidgetItem*>   m_languageToItem;
    QMap<QTreeWidgetItem*,QLanguage*>   m_ItemToLanguage;
private slots:
    void on_cancelBtn_clicked();
    void on_okBtn_clicked();
};

#endif // QDELLANGUAGEDIALOG_H
