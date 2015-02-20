#ifndef QLINEEDITDIALOG_H
#define QLINEEDITDIALOG_H

#include <QDialog>

namespace Ui {
class QLineEditDialog;
}

class QLineEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QLineEditDialog(QWidget *parent = 0);
    ~QLineEditDialog();

    void    setText(const QString &text);
    QString getText();
    int     getRet();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::QLineEditDialog *ui;
    int     m_ret;
};

#endif // QLINEEDITDIALOG_H
