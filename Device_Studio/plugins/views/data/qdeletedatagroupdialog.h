#ifndef QDELETEDATAGROUPDIALOG_H
#define QDELETEDATAGROUPDIALOG_H

#include <QDialog>
#include <QMap>
#include <QTreeWidget>

namespace Ui {
class QDeleteDataGroupDialog;
}

class QBaseListView;
class QDataManager;
class QDataGroup;

class QDeleteDataGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDeleteDataGroupDialog(QDataManager * manager,QWidget *parent = 0);
    ~QDeleteDataGroupDialog();

protected slots:
    void    groupClicked(QTreeWidgetItem * item);
private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::QDeleteDataGroupDialog *ui;
    QBaseListView       *m_listView;
    QDataManager        *m_dataManager;

    QMap<QTreeWidgetItem*,QDataGroup*>  m_itemToGroup;
};

#endif // QDELETEDATAGROUPDIALOG_H
