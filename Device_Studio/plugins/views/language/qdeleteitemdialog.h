#ifndef QDELETEITEMDIALOG_H
#define QDELETEITEMDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QTreeWidget>

namespace Ui {
class QDeleteItemDialog;
}

class QBaseListView;

class QDeleteItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDeleteItemDialog(const QStringList & list,QWidget *parent = 0);
    ~QDeleteItemDialog();
    QStringList getSelection();
protected slots:
    void    itemClicked(QTreeWidgetItem *item);
private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::QDeleteItemDialog *ui;
    QBaseListView       *m_listView;
    QMap<QString,QTreeWidgetItem*>  m_keyToItem;
    QMap<QTreeWidgetItem*,QString>  m_itemToKey;
    QStringList         m_selectList;
};

#endif // QDELETEITEMDIALOG_H
