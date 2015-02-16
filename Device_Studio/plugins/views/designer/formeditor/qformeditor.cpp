#include "qformeditor.h"

#include "qformpanel.h"

#include "../../../../libs/kernel/host/qabstractwidgethost.h"

#include <QPainter>

QFormEditor::QFormEditor(QWidget* parent):
    QStackedWidget(parent)
{
    this->setAutoFillBackground(false);
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
    QFormPanel *panel = m_hostToPanel.value(host);
    if(panel != NULL)
    {
        panel->select(host);
        setCurrentWidget(m_hostToPanel.value(host)->getOwner());
    }
    else
    {
        emit select(NULL);
    }
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
