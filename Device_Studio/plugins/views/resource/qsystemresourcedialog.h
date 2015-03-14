#ifndef QSYSTEMRESOURCEDIALOG_H
#define QSYSTEMRESOURCEDIALOG_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class QSystemResourceDialog;
}

class QBaseListView;

class QSystemResourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QSystemResourceDialog(QWidget *parent = 0);
    ~QSystemResourceDialog();

protected:
    void updateCheck();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void updateSystemResource();

    void itemClicked(QTreeWidgetItem * item);
private:
    Ui::QSystemResourceDialog *ui;
    QBaseListView       *m_resourceList;
    QMap<QString,QTreeWidgetItem*>  m_nameToGroup;
    QMap<QString,bool>              m_checked;
};

#endif // QSYSTEMRESOURCEDIALOG_H
