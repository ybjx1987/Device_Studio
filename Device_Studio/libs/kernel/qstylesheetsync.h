#ifndef QSTYLESHEETSYNC_H
#define QSTYLESHEETSYNC_H

#include <QObject>

class QAbstractHost;
class QStyleSheetManager;
class QAbstractWidgetHost;

class QStyleSheetItem;

class QStyleSheetSync : public QObject
{
    Q_OBJECT
public:
    explicit QStyleSheetSync(QStyleSheetManager *manager,
                             const QList<QAbstractWidgetHost*> &forms,
                             QObject *parent = 0);
    ~QStyleSheetSync();

    void    addForm(QAbstractHost * form);
    void    delForm(QAbstractHost * form);
protected:
    QList<QAbstractHost*> getWidgetByType(const QString & type);
    QList<QAbstractHost*> getWidgetByName(const QString & name);

    QList<QStyleSheetItem*> getItemByName(const QString & name);
    QList<QStyleSheetItem*> getItemByType(const QString & type);

    void    updateStyleSheet(QAbstractHost * host);
signals:

protected slots:
    void    needUpdateStyleSheet(const QList<QStyleSheetItem*> &items);
protected:
    QList<QAbstractHost*>           m_forms;
    QStyleSheetManager              *m_styleSheetManager;
};

#endif // QSTYLESHEETSYNC_H
