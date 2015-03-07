#ifndef QNEWTITLEDIALOG_H
#define QNEWTITLEDIALOG_H

#include <QDialog>

namespace Ui {
class QNewTitleDialog;
}

class QNewTitleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewTitleDialog(QWidget *parent = 0);
    ~QNewTitleDialog();

private:
    Ui::QNewTitleDialog *ui;
};

#endif // QNEWTITLEDIALOG_H
