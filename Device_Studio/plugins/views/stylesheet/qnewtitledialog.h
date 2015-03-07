#ifndef QNEWTITLEDIALOG_H
#define QNEWTITLEDIALOG_H

#include <QDialog>
#include <QCheckBox>

namespace Ui {
class QNewTitleDialog;
}

class QValidatorEdit;
class QStyleSheetItem;

class QNewTitleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewTitleDialog(QStyleSheetItem * item,QWidget *parent = 0);
    ~QNewTitleDialog();

private slots:
    void on_okBtn_clicked();

    void on_cancleBtn_clicked();

    void updateComplete();
private:
    Ui::QNewTitleDialog *ui;
    QValidatorEdit      *m_nameEdit;
    QList<QCheckBox*>   m_subControls;
    QStyleSheetItem     *m_item;
};

#endif // QNEWTITLEDIALOG_H
