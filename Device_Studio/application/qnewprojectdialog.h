#ifndef QNEWPROJECTDIALOG_H
#define QNEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class QNewProjectDialog;
}

class QValidatorEdit;

class QNewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewProjectDialog(QWidget *parent = 0);
    ~QNewProjectDialog();

    QString     getName();
    QString     getPath();

private slots:
    void on_fileBtn_clicked();

    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::QNewProjectDialog *ui;

    QValidatorEdit      *m_projectName;

    QString             m_name;
    QString             m_path;
};

#endif // QNEWPROJECTDIALOG_H
