#include "qpropertyeditorpane.h"

#include "qpropertyeditorfactory.h"
#include "editor/qabstractpropertyeditor.h"

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
    m_resetButton->setVisible(m_property->parent() == NULL);
    m_resetButton->setProperty("no-ManhattanStyle",true);

    connect(m_resetButton,SIGNAL(clicked()),m_property,SLOT(reset()));
    connect(m_property,SIGNAL(valueChanged(QVariant,QVariant)),
            this,SLOT(propertyRefresh()));

    m_widget = QPropertyEditorFactory::createEditor(m_property->metaObject()->className(),m_property);
    connect(m_widget,SIGNAL(valueChanged(QVariant)),
            this,SLOT(propertyEdit(QVariant)));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_widget);
    layout->addWidget(m_resetButton);

    this->setLayout(layout);
    QAbstractProperty * pro = m_property;
    while(pro->getParent() != NULL)
    {
        pro = pro->getParent();
    }
    setProperty("propertyValue",pro->getValue());
}

QPropertyEditorPane::~QPropertyEditorPane()
{
    QAbstractProperty * pro = m_property;
    while(pro->getParent() != NULL)
    {
        pro = pro->getParent();
    }
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
    setProperty("propertyValue",m_property->getValue());
}

void QPropertyEditorPane::propertyEdit(const QVariant &value)
{
    emit propertyValueEdit(m_property,value);
}
