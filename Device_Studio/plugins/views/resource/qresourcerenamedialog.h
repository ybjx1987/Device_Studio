#ifndef QRESOURCERENAMEDIALOG_H
#define QRESOURCERENAMEDIALOG_H

#include <QDialog>

namespace Ui {
class QResourceRenameDialog;
}

class QValidatorEdit;

class QResourceRenameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QResourceRenameDialog(const QString & oldName,
                                   const QStringList & list,QWidget *parent = 0);
    ~QResourceRenameDialog();

    int getRet();
    QString getNewName();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::QResourceRenameDialog *ui;

    QValidatorEdit      *m_nameEdit;

    int                 m_ret;
};

#endif // QRESOURCERENAMEDIALOG_H
