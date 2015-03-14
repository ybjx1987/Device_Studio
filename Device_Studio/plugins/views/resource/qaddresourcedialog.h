#ifndef QADDRESOURCEDIALOG_H
#define QADDRESOURCEDIALOG_H

#include <QDialog>

namespace Ui {
class QAddResourceDialog;
}

class QAddResourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QAddResourceDialog(QWidget *parent = 0);
    ~QAddResourceDialog();
protected slots:
    void fromSystem();
    void fromLocal();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::QAddResourceDialog *ui;

    QString     m_resourceType;
};

#endif // QADDRESOURCEDIALOG_H
