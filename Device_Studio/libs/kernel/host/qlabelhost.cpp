#include "qlabelhost.h"

#include "../property/qstringproperty.h"
#include "../property/qboolproperty.h"
#include "../property/qalignmentproperty.h"

#include <QLabel>

QLabelHost::QLabelHost(QAbstractWidgetHost * parent):
    QFrameHost(parent)
{
    setProperty("needFrame",false);
    setProperty("acceptDrop",false);
}

QAbstractHostInfo * QLabelHost::getHostInfo()
{
    QWidgetHostInfo *info = new QWidgetHostInfo;
    info->m_index = 31;
    info->m_metaObject = &(QLabelHost::staticMetaObject);
    info->m_name = "label";
    info->m_showGroup = tr("Display Widgets");
    info->m_showIcon = ":/inner/images/widgets/label.png";
    info->m_showName = tr("Label");
    return info;
}

void QLabelHost::createObject()
{
    m_object = new QLabel;
    m_object->setObjectName("label");
    m_object->setProperty("geometry",QRect(0,0,80,20));
    m_object->setProperty("text","label");
}

void QLabelHost::initProperty()
{
    QFrameHost::initProperty();

    QAbstractProperty * pro;

    pro = new QStringProperty;
    pro->setName("text");
    pro->setShowName(tr("Text"));
    pro->setGroup("Attributes");
    insertProperty(pro,1);

    pro = new QBoolProperty;
    pro->setName("wordWrap");
    pro->setShowName(tr("Word Wrap"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QAlignmentProperty;
    pro->setName("alignment");
    pro->setShowName(tr("Alignment"));
    pro->setGroup("Attributes");
    insertProperty(pro);
}

void QLabelHost::setText(const QString &text)
{
    setPropertyValue("text",text);
}

QString QLabelHost::getText()
{
    return getPropertyValue("text").toString();
}

void QLabelHost::setWordWrap(bool wordWrap)
{
    setPropertyValue("wordWrap",wordWrap);
}

bool QLabelHost::getWordWrap()
{
    return getPropertyValue("wordWrap").toBool();
}

void QLabelHost::setAlignment(int alignment)
{
    setPropertyValue("alignment",alignment);
}

int QLabelHost::getAlignment()
{
    return getPropertyValue("alignment").toInt();
}
