#ifndef QNEWLANGUAGEDIALOG_H
#define QNEWLANGUAGEDIALOG_H

#include "../.././../libs/platform/qlanguageid.h"

#include <QDialog>

namespace Ui {
class QNewLanguageDialog;
}

class QNewLanguageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewLanguageDialog(QWidget *parent = 0);
    ~QNewLanguageDialog();

    QString getLanguageID();
private:
    Ui::QNewLanguageDialog *ui;
protected:
    QList<QLanguageInfo>    m_languageInfos;
    QString                 m_id;
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // QNEWLANGUAGEDIALOG_H
