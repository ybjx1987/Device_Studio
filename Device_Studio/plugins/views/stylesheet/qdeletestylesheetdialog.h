#ifndef QDELETESTYLESHEETDIALOG_H
#define QDELETESTYLESHEETDIALOG_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class QDeleteStyleSheetDialog;
}

class QStyleSheetManager;
class QBaseListView;
class QStyleSheetGroup;

class QDeleteStyleSheetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDeleteStyleSheetDialog(QWidget *parent = 0);
    ~QDeleteStyleSheetDialog();

    void  init(QStyleSheetManager * manager);
protected:
    bool    eventFilter(QObject *, QEvent *);
private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void itemClicked(QTreeWidgetItem * item);

    void selectAll();
    void clearAll();
private:
    Ui::QDeleteStyleSheetDialog *ui;
    QBaseListView       *m_listView;
    QStyleSheetManager  *m_manager;
    QMap<QTreeWidgetItem*,QStyleSheetGroup*>    m_itemToGroup;
};

#endif // QDELETESTYLESHEETDIALOG_H
