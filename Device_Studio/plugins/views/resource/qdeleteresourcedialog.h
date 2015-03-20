#ifndef QDELETERESOURCEDIALOG_H
#define QDELETERESOURCEDIALOG_H

#include <QDialog>
#include <QMap>
#include <QTreeWidget>

class QBaseListView;
class QResourceFile;

namespace Ui {
class QDeleteResourceDialog;
}

class QDeleteResourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDeleteResourceDialog(QWidget *parent = 0);
    ~QDeleteResourceDialog();

    QList<QResourceFile*>   getSelectFile();
protected slots:
    void itemClicked(QTreeWidgetItem * item);
private slots:
    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::QDeleteResourceDialog *ui;

    QBaseListView       *m_listView;

    QMap<QTreeWidgetItem*,QResourceFile*>   m_itemToFile;
    QMap<QString,QTreeWidgetItem*>      m_nameToGroup;

    QList<QResourceFile*>               m_selectFile;
};

#endif // QDELETERESOURCEDIALOG_H
