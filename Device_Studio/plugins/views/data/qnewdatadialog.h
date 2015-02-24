#ifndef QNEWDATADIALOG_H
#define QNEWDATADIALOG_H

#include <QDialog>

namespace Ui {
class QNewDataDialog;
}

class QDataManager;
class QValidatorEdit;
class QAbstractHostInfo;

class QNewDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewDataDialog(QDataManager * manager,QWidget *parent = 0);
    ~QNewDataDialog();
protected slots:
    void groupChanged();
private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::QNewDataDialog *ui;
    QDataManager    *m_dataManager;
    QValidatorEdit  *m_nameEdit;
    QList<QAbstractHostInfo*> m_typeList;
};

#endif // QNEWDATADIALOG_H
