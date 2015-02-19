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
protected:
    QBaseListView   *m_listview;
    QMap<QLanguage*,QTreeWidgetItem*>   m_languageToItem;
    QMap<QTreeWidgetItem*,QLanguage*>   m_ItemToLanguage;
};

#endif // QDELLANGUAGEDIALOG_H
