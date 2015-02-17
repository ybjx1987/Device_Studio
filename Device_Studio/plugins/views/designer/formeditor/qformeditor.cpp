#include "qformeditor.h"

#include "qformpanel.h"

#include "../../../../libs/kernel/host/qabstractwidgethost.h"
#include "../../../../libs/platform/qsoftactionmap.h"

#include <QPainter>
#include <QAction>

QFormEditor::QFormEditor(QWidget* parent):
    QStackedWidget(parent),
    m_selectHost(NULL)
{
    this->setAutoFillBackground(false);

    QAction *action;

//    QStringList list;
//    list<<"designer.left"<<"designer.top"<<"designer.right"
//       <<"designer.bottom"<<"designer.v-center"<<"designer.h-center"
//      <<"designer.same-width"<<"designer.same-height"<<"designer.same-rect";
//    foreach(QString str,list)
//    {
//        action = QSoftActionMap::getAction(str);
//        if(action != NULL)
//        {
//            connect(action,SIGNAL(triggered()),this,SLOT(sameLeft()));
//        }
//    }

    action = QSoftActionMap::getAction("designer.left");
    if(action != NULL)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(sameLeft()));
    }

    action = QSoftActionMap::getAction("designer.top");
    if(action != NULL)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(sameTop()));
    }

    action = QSoftActionMap::getAction("designer.right");
    if(action != NULL)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(sameRight()));
    }

    action = QSoftActionMap::getAction("designer.bottom");
    if(action != NULL)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(sameBottom()));
    }

    action = QSoftActionMap::getAction("designer.v-center");
    if(action != NULL)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(sameVCenter()));
    }

    action = QSoftActionMap::getAction("designer.h-center");
    if(action != NULL)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(sameHCenter()));
    }

    action = QSoftActionMap::getAction("designer.same-width");
    if(action != NULL)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(sameWidth()));
    }

    action = QSoftActionMap::getAction("designer.same-height");
    if(action != NULL)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(sameHeight()));
    }

    action = QSoftActionMap::getAction("designer.same-rect");
    if(action != NULL)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(sameGeometry()));
    }
}

void QFormEditor::setHostList(QList<QAbstractWidgetHost *> list)
{
    clear();

    foreach(QAbstractWidgetHost * host,list)
    {
        QFormPanel * panel = new QFormPanel(host);
        m_panelToHost.insert(panel,host);
        m_hostToPanel.insert(host,panel);
        connect(panel,SIGNAL(hostSelected(QAbstractWidgetHost*)),
                this,SIGNAL(select(QAbstractWidgetHost*)));
        QScrollArea *area = new QScrollArea;
        area->setWidget(panel);
        panel->setOwner(area);
        area->viewport()->setStyleSheet(
                    "#"+area->viewport()->objectName()+"{background-color:rgb(255,255,255);}");
        addWidget(area);
    }
}

void QFormEditor::clear()
{
    showHost(NULL);
    qDeleteAll(m_hostToPanel.values());
    m_panelToHost.clear();
    m_hostToPanel.clear();
}

void QFormEditor::showHost(QAbstractWidgetHost *host)
{
    if(m_selectHost == host)
    {
        return;
    }
    emit formSelect(host);
    QFormPanel *panel = m_hostToPanel.value(host);
    if(m_selectHost != NULL)
    {
        QFormPanel * p = m_hostToPanel.value(m_selectHost);
        disconnect(p,SIGNAL(updateAction()),
                this,SLOT(updateAction()));
    }
    m_selectHost = host;
    if(panel != NULL)
    {
        panel->select(host);
        setCurrentWidget(m_hostToPanel.value(host)->getOwner());
        connect(panel,SIGNAL(updateAction()),this,SLOT(updateAction()));
    }
    else
    {
        emit select(NULL);
    }
    updateAction();
}

void QFormEditor::selectHost(QAbstractWidgetHost *host)
{
    if(m_selectHost == NULL)
    {
        return;
    }
    QFormPanel *panel = m_hostToPanel.value(m_selectHost);

    panel->select(host);
}

void QFormEditor::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(this->rect(),QColor(255,255,255));
}

QUndoStack *QFormEditor::getUndoStack(QAbstractWidgetHost *host)
{
    QFormPanel *panel = m_hostToPanel.value(host);
    if(panel!=NULL)
    {
        return panel->getUndoStack();
    }
    return NULL;
}

void QFormEditor::sameLeft()
{
    if(m_selectHost == NULL)
    {
        return;
    }
    QFormPanel *panel = m_hostToPanel.value(m_selectHost);

    if(panel != NULL)
    {
        panel->sameLeft();
    }
}

void QFormEditor::sameTop()
{
    if(m_selectHost == NULL)
    {
        return;
    }
    QFormPanel *panel = m_hostToPanel.value(m_selectHost);

    if(panel != NULL)
    {
        panel->sameTop();
    }
}

void QFormEditor::sameRight()
{
    if(m_selectHost == NULL)
    {
        return;
    }
    QFormPanel *panel = m_hostToPanel.value(m_selectHost);

    if(panel != NULL)
    {
        panel->sameRight();
    }
}

void QFormEditor::sameBottom()
{
    if(m_selectHost == NULL)
    {
        return;
    }
    QFormPanel *panel = m_hostToPanel.value(m_selectHost);

    if(panel != NULL)
    {
        panel->sameBottom();
    }
}

void QFormEditor::sameHCenter()
{
    if(m_selectHost == NULL)
    {
        return;
    }
    QFormPanel *panel = m_hostToPanel.value(m_selectHost);

    if(panel != NULL)
    {
        panel->sameHCenter();
    }
}

void QFormEditor::sameVCenter()
{
    if(m_selectHost == NULL)
    {
        return;
    }
    QFormPanel *panel = m_hostToPanel.value(m_selectHost);

    if(panel != NULL)
    {
        panel->sameVCenter();
    }
}

void QFormEditor::sameWidth()
{
    if(m_selectHost == NULL)
    {
        return;
    }
    QFormPanel *panel = m_hostToPanel.value(m_selectHost);

    if(panel != NULL)
    {
        panel->sameWidth();
    }
}

void QFormEditor::sameHeight()
{
    if(m_selectHost == NULL)
    {
        return;
    }
    QFormPanel *panel = m_hostToPanel.value(m_selectHost);

    if(panel != NULL)
    {
        panel->sameHeight();
    }
}

void QFormEditor::sameGeometry()
{
    if(m_selectHost == NULL)
    {
        return;
    }
    QFormPanel *panel = m_hostToPanel.value(m_selectHost);

    if(panel != NULL)
    {
        panel->sameGeometry();
    }
}

void QFormEditor::updateAction()
{
    bool enable = false;

    if(m_selectHost != NULL)
    {
        QFormPanel * panel = m_hostToPanel.value(m_selectHost);
        enable = panel->enableAction();
    }

    QAction *action;

    QStringList list;
    list<<"designer.left"<<"designer.top"<<"designer.right"
       <<"designer.bottom"<<"designer.v-center"<<"designer.h-center"
      <<"designer.same-width"<<"designer.same-height"<<"designer.same-rect";
    foreach(QString str,list)
    {
        action = QSoftActionMap::getAction(str);
        if(action != NULL)
        {
            action->setEnabled(enable);
        }
    }
}
