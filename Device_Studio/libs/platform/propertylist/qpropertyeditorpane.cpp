#include "qpropertyeditorpane.h"

#include "qcommoneditor.h"

#include "../../kernel/property/qabstractproperty.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QEvent>
#include <QApplication>

QPropertyEditorPane::QPropertyEditorPane(QAbstractProperty* property,QWidget* parent):
    QWidget(parent),
    m_property(property),
    m_widget(NULL)
{
    setFocusPolicy(Qt::StrongFocus);
    m_resetButton = new QToolButton(this);
    m_resetButton->setVisible(m_property->getResetable());
    m_resetButton->setIcon(QIcon(":/inner/images/reset.png"));
    m_resetButton->setIconSize(QSize(8,8));
    m_resetButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::MinimumExpanding));
    m_resetButton->setFocusProxy(this);
    m_resetButton->setFocusPolicy(Qt::NoFocus);
    m_resetButton->setEnabled(m_property->isModified());

    connect(m_resetButton,SIGNAL(clicked()),m_property,SLOT(reset()));
    connect(m_property,SIGNAL(valueChanged(QVariant,QVariant)),
            this,SLOT(propertyRefresh()));

    if(m_widget == NULL)
    {
        m_widget = new QCommonEditor(property,this);
    }

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_widget);
    layout->addWidget(m_resetButton);

    this->setLayout(layout);
}

void QPropertyEditorPane::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(),Qt::white);
}

bool QPropertyEditorPane::eventFilter(QObject *o, QEvent *e)
{
    if(o == m_widget && e->type() == QEvent::FocusOut)
    {
        qApp->sendEvent(this,e);
    }
    return QWidget::eventFilter(o,e);
}

void QPropertyEditorPane::propertyRefresh()
{
    m_resetButton->setEnabled(m_property->isModified());
}
