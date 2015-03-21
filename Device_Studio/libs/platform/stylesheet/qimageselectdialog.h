#ifndef QIMAGESELECTDIALOG_H
#define QIMAGESELECTDIALOG_H

#include <QDialog>

namespace Ui {
class QImageSelectDialog;
}

class QProjectResourceView;

class QResourceFile;

class QImageSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QImageSelectDialog(QWidget *parent = 0);
    ~QImageSelectDialog();
    QResourceFile * getSelect();
protected slots:
    void    select(QResourceFile * file);
private:
    Ui::QImageSelectDialog *ui;
    QProjectResourceView    *m_resourceView;
    QResourceFile           *m_resourceFile;
};

#endif // QIMAGESELECTDIALOG_H
