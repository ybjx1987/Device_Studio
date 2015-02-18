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

    void    selectHost(QAbstractWidgetHost * host);
signals:
    void    select(QAbstractWidgetHost* host);
    void    formSelect(QAbstractWidgetHost * host);
protected:
    void    paintEvent(QPaintEvent *);
protected slots:
    void    updateAction();
    void    sameLeft();
    void    sameTop();
    void    sameRight();
    void    sameBottom();
    void    sameVCenter();
    void    sameHCenter();
    void    sameWidth();
    void    sameHeight();
    void    sameGeometry();
protected:
    QMap<QFormPanel* ,QAbstractWidgetHost*> m_panelToHost;
    QMap<QAbstractWidgetHost*,QFormPanel*>  m_hostToPanel;

    QAbstractWidgetHost*        m_selectHost;
};

#endif // QFORMEDITOR_H
