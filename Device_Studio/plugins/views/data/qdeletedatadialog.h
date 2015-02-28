#ifndef QDELETEDATADIALOG_H
#define QDELETEDATADIALOG_H

#include <QDialog>

#include <QTreeWidget>

namespace Ui {
class QDeleteDataDialog;
}

class QBaseListView;
class QDataManager;
class QDataGroup;
class QAbstractDataHost;

class QDeleteDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDeleteDataDialog(QDataManager * manager,QWidget *parent = 0);
    ~QDeleteDataDialog();

protected slots:
    void    itemClicked(QTreeWidgetItem* item);

    void    selectAll();
    void    clearAll();
protected:
    bool    eventFilter(QObject *, QEvent *);
    void    showMenu(const QPoint &pt);
private slots:
    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::QDeleteDataDialog *ui;
    QBaseListView   *m_listView;
    QDataManager    *m_dataManager;

    QMap<QTreeWidgetItem*,QDataGroup*>      m_itemToGroup;
    QMap<QTreeWidgetItem*,QAbstractDataHost*>   m_itemToData;

    QList<QAction*>     m_actions;
};

#endif // QDELETEDATADIALOG_H
