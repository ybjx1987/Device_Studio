#ifndef QNEWITEMDIALOG_H
#define QNEWITEMDIALOG_H

#include "../../../libs/platform/qvalidatoredit.h"

#include <QDialog>

namespace Ui {
class QNewItemDialog;
}

class QNewItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewItemDialog(const QStringList &list,QWidget *parent = 0);
    ~QNewItemDialog();

    QString getKey();

private:
    Ui::QNewItemDialog *ui;
protected:
    QValidatorEdit   *m_keyEdit;
    QString          m_key;
private slots:
    void on_okBtn_clicked();
    void on_cancelBtn_clicked();
};

#endif // QNEWITEMDIALOG_H
