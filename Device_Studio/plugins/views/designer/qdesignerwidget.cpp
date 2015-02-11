#include "qdesignerwidget.h"

#include "qwidgetboxlist.h"
#include "formeditor/qformeditor.h"

#include "../../../libs/platform/propertylist/qpropertylistview.h"
#include "../../../libs/platform/styledbar.h"

#include "../../../libs/platform/minisplitter.h"

#include "../../../libs/kernel/host/qhostfactory.h"
#include "../../../libs/kernel/host/qabstracthost.h"
#include "../../../libs/platform/qsoftcore.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/kernel/qproject.h"
#include "../../../libs/platform/qsoftcore.h"

#include <QVBoxLayout>

QDesignerWidget::QDesignerWidget(QWidget * parent ):
    QAbstractPageWidget(parent),
    m_propertyView(new QPropertyListView(this)),
    m_propertyViewBar(new StyledBar(this)),
    m_widgetBoxList(new QWidgetBoxList(this)),
    m_widgetBoxListBar(new StyledBar(this)),
    m_formEditor(new QFormEditor(this)),
    m_formEditorBar(new StyledBar(this))
{
    MiniSplitter  *splitter = new MiniSplitter(this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(splitter);
    setLayout(layout);

    QWidget * wid = new QWidget;
    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_widgetBoxListBar);
    layout->addWidget(m_widgetBoxList);
    wid->setLayout(layout);
    splitter->addWidget(wid);

    wid = new QWidget;
    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_formEditorBar);
    layout->addWidget(m_formEditor);
    wid->setLayout(layout);
    splitter->addWidget(wid);

    wid = new QWidget;
    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_propertyViewBar);
    layout->addWidget(m_propertyView);
    wid->setLayout(layout);
    splitter->addWidget(wid);

    splitter->setStretchFactor(0,0);
    splitter->setStretchFactor(1,1);
    splitter->setStretchFactor(2,0);

    connect(QSoftCore::getInstance()->getProject(),SIGNAL(hostAdded(QAbstractWidgetHost*,int)),
            this,SLOT(formAdded(QAbstractWidgetHost*,int)));
}

void QDesignerWidget::formAdded(QAbstractWidgetHost *host, int index)
{
    m_formEditor->setHostList(QList<QAbstractWidgetHost*>()<<host);
}

