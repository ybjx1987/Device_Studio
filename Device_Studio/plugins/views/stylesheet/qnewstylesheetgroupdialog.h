#ifndef QNEWSTYLESHEETGROUPDIALOG_H
#define QNEWSTYLESHEETGROUPDIALOG_H

#include <QDialog>

namespace Ui {
class QNewStyleSheetGroupDialog;
}

class QValidatorEdit;

class QNewStyleSheetGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewStyleSheetGroupDialog(const QStringList & list,QWidget *parent = 0);
    ~QNewStyleSheetGroupDialog();

    QString getName();
private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::QNewStyleSheetGroupDialog *ui;
    QValidatorEdit      *m_nameEdit;
    QString             m_name;
};

#endif // QNEWSTYLESHEETGROUPDIALOG_H
