#include "qscrollbarhost.h"

#include <QScrollBar>
#include <QVariant>

QScrollBarHost::QScrollBarHost(QAbstractWidgetHost * parent):
    QAbstractSliderHost(parent)
{

}

void QScrollBarHost::createObject()
{
    m_object = new QScrollBar;
    m_object->setObjectName("scrollbar");
    m_object->setProperty("geometry",QRect(0,0,100,20));
    m_object->setProperty("orientation",Qt::Horizontal);
}

void QScrollBarHost::initProperty()
{
    QAbstractSliderHost::initProperty();

}

QAbstractHostInfo *QScrollBarHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo();
    info->m_metaObject = &(QScrollBarHost::staticMetaObject);
    info->m_index = 14;
    info->m_showGroup = tr("Input Widgets");
    info->m_showIcon = ":/inner/images/widgets/hscrollbar.png";
    info->m_showName = tr("Scroll Bar");
    info->m_name = "scrollBar";
    return info;
}
