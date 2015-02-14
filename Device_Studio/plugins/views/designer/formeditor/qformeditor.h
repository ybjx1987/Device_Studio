#ifndef QFORMEDITOR_H
#define QFORMEDITOR_H

#include <QStackedWidget>
#include <QMap>
#include <QUndoStack>
class QFormPanel;
class QAbstractWidgetHost;

class QFormEditor: public QStackedWidget
{
    Q_OBJECT
public:
    QFormEditor(QWidget * parent = NULL);

    void    setHostList(QList<QAbstractWidgetHost*> list);

    void    clear();

    void    showHost(QAbstractWidgetHost * host);

    QUndoStack* getUndoStack(QAbstractWidgetHost * host);

signals:
    void    select(QAbstractWidgetHost* host);
protected:
    void    paintEvent(QPaintEvent *);
protected:
    QMap<QFormPanel* ,QAbstractWidgetHost*> m_panelToHost;
    QMap<QAbstractWidgetHost*,QFormPanel*>  m_hostToPanel;
};

#endif // QFORMEDITOR_H
