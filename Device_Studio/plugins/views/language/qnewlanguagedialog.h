#ifndef QNEWLANGUAGEDIALOG_H
#define QNEWLANGUAGEDIALOG_H

#include <QDialog>

namespace Ui {
class QNewLanguageDialog;
}

class LanguageInfo
{
public:
    QString m_name;
    QString m_icon;
    QString m_id;
};

class QNewLanguageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QNewLanguageDialog(QWidget *parent = 0);
    ~QNewLanguageDialog();

    LanguageInfo getLanguageInfo();
protected:
    void    load();
private:
    Ui::QNewLanguageDialog *ui;
protected:
    QList<LanguageInfo>     m_languageInfos;
    LanguageInfo            m_languageInfo;
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // QNEWLANGUAGEDIALOG_H
