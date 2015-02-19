#ifndef QNEWALLITEMDIALOG_H
#define QNEWALLITEMDIALOG_H

#include "../../../libs/platform/qvalidatoredit.h"

#include <QDialog>

namespace Ui {
class QNewAllItemDialog;
}

class QNewAllItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewAllItemDialog(const QStringList &list,QWidget *parent = 0);
    ~QNewAllItemDialog();

    QString getKey();
private:
    Ui::QNewAllItemDialog *ui;
protected:
    QValidatorEdit      *m_keyEdit;
    QString             m_key;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // QNEWALLITEMDIALOG_H
