#ifndef QRENAMEDIALOG_H
#define QRENAMEDIALOG_H

#include "platformlibglobal.h"
#include <QDialog>

namespace Ui {
class QRenameDialog;
}

class QValidatorEdit;

class PLATFORM_EXPORT QRenameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QRenameDialog(QWidget *parent = 0);
    ~QRenameDialog();

    void setNameList(const QStringList &list);
    void    setOldName(const QString &name);
    QString getNewName();
    int     getRet();
private slots:
    void on_okbtn_clicked();

    void on_cancelbtn_clicked();

private:
    Ui::QRenameDialog *ui;

    QValidatorEdit    *m_nameEdit;

    int                 m_ret;
};

#endif // QRENAMEDIALOG_H
