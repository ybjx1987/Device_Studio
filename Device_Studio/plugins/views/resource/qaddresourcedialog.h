#ifndef QADDRESOURCEDIALOG_H
#define QADDRESOURCEDIALOG_H

#include <QDialog>
#include <QMap>
#include <QTreeWidget>

namespace Ui {
class QAddResourceDialog;
}

class QBaseListView;

class ResourceFileInfo
{
public:
    QString     m_path;
    QString     m_sourcePath;
    QString     m_type;
};

class QAddResourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QAddResourceDialog(QWidget *parent = 0);
    ~QAddResourceDialog();
protected:
    void addResource(ResourceFileInfo * info);

    QStringList getEnabledString(QTreeWidgetItem * item);

    void    updateName();
protected slots:
    void fromSystem();
    void fromLocal();
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void    itemRemove();
    void    itemRename();
private:
    Ui::QAddResourceDialog *ui;
    QBaseListView       *m_listview;

    QMap<ResourceFileInfo*,QTreeWidgetItem*> m_resourceToItem;
    QMap<QTreeWidgetItem*,ResourceFileInfo*> m_itemToResource;
    QMap<QString,ResourceFileInfo*>          m_nameToInfo;
    QMap<QString,QTreeWidgetItem*>           m_nameToGroup;
};

#endif // QADDRESOURCEDIALOG_H
