#ifndef QNEWTITLEDIALOG_H
#define QNEWTITLEDIALOG_H

#include <QDialog>
#include <QCheckBox>

namespace Ui {
class QNewTitleDialog;
}

class QValidatorEdit;

class QNewTitleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewTitleDialog(QWidget *parent = 0);
    ~QNewTitleDialog();

private slots:
    void on_okBtn_clicked();

    void on_cancleBtn_clicked();

    void updateComplete();
private:
    Ui::QNewTitleDialog *ui;
    QValidatorEdit      *m_nameEdit;
    QList<QCheckBox*>   m_subControls;
};

#endif // QNEWTITLEDIALOG_H
