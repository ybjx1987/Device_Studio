#ifndef QCOMMONPROPERTYEDITDIALOG_H
#define QCOMMONPROPERTYEDITDIALOG_H

#include <QDialog>
#include <QVariant>

class QAbstractProperty;

namespace Ui {
class QCommonPropertyEditDialog;
}

class QCommonPropertyEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QCommonPropertyEditDialog(QAbstractProperty * pro,QWidget *parent = 0);
    ~QCommonPropertyEditDialog();

    QVariant getValue();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void propertyValueEdit(QAbstractProperty * property,const QVariant &value);
private:
    Ui::QCommonPropertyEditDialog *ui;
    QAbstractProperty       *m_property;
    QVariant                m_value;
};

#endif // QCOMMONPROPERTYEDITDIALOG_H
