#ifndef QNEWDATAGROUPDIALOG_H
#define QNEWDATAGROUPDIALOG_H

#include <QDialog>

namespace Ui {
class QNewDataGroupDialog;
}

class QValidatorEdit;

class QNewDataGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewDataGroupDialog(const QStringList & list,QWidget *parent = 0);
    ~QNewDataGroupDialog();

    QString getName();
private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::QNewDataGroupDialog *ui;
    QValidatorEdit          *m_nameEdit;
    QString                 m_name;
};

#endif // QNEWDATAGROUPDIALOG_H
