#ifndef QDELETEDATADIALOG_H
#define QDELETEDATADIALOG_H

#include <QDialog>

namespace Ui {
class QDeleteDataDialog;
}

class QBaseListView;
class QDataManager;

class QDeleteDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDeleteDataDialog(QDataManager * manager,QWidget *parent = 0);
    ~QDeleteDataDialog();

private:
    Ui::QDeleteDataDialog *ui;
    QBaseListView   *m_listView;
    QDataManager    *m_dataManager;
};

#endif // QDELETEDATADIALOG_H
