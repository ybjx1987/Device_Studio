#ifndef QNEWPROJECTDIALOG_H
#define QNEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class QNewProjectDialog;
}

class QNewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewProjectDialog(QWidget *parent = 0);
    ~QNewProjectDialog();

private:
    Ui::QNewProjectDialog *ui;
};

#endif // QNEWPROJECTDIALOG_H
