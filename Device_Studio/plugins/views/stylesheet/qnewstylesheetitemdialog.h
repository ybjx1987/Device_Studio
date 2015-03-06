#ifndef QNEWSTYLESHEETITEMDIALOG_H
#define QNEWSTYLESHEETITEMDIALOG_H

#include <QDialog>

namespace Ui {
class QNewStyleSheetItemDialog;
}

class QStyleSheetManager;

class QNewStyleSheetItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewStyleSheetItemDialog(QStyleSheetManager * manager,QWidget *parent = 0);
    ~QNewStyleSheetItemDialog();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::QNewStyleSheetItemDialog *ui;
    QStyleSheetManager      *m_manager;
};

#endif // QNEWSTYLESHEETITEMDIALOG_H
