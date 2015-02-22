#ifndef QSTRINGEDITORDIALOG_H
#define QSTRINGEDITORDIALOG_H

#include <QDialog>

namespace Ui {
class QStringEditorDialog;
}

class QBaseListView;

class QStringEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QStringEditorDialog(QWidget *parent = 0);
    ~QStringEditorDialog();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::QStringEditorDialog *ui;
protected:
    QBaseListView       *m_listView;
};

#endif // QSTRINGEDITORDIALOG_H
