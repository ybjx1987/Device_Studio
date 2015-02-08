#include "qframehost.h"

#include "../property/qenumproperty.h"
#include "../qvarianttype.h"

#include <QFrame>

QFrameHost::QFrameHost(QAbstractWidgetHost * parent):
    QWidgetHost(parent)
{

}

void QFrameHost::createObject()
{
    m_object = new QFrame();
    m_object->setObjectName("frame");
    m_object->setProperty("geometry",QRect(0,0,100,100));
}

void QFrameHost::initProperty()
{
    QWidgetHost::initProperty();

    QAbstractProperty * pro;

    pro = new QEnumProperty();
    pro->setName("frameShape");
    pro->setShowName(tr("FrameShape"));
    pro->setGroup("Attributes");

    ComboItems items;
    tagComboItem item;

    item.m_text=tr("NoFrame");
    item.m_value=QFrame::NoFrame;
    items.append(item);

    item.m_text=tr("Box");
    item.m_value=QFrame::Box;
    items.append(item);

    item.m_text=tr("Panel");
    item.m_value=QFrame::Panel;
    items.append(item);

    item.m_text=tr("StyledPanel");
    item.m_value=QFrame::StyledPanel;
    items.append(item);

    item.m_text=tr("HLine");
    item.m_value=QFrame::HLine;
    items.append(item);

    item.m_text=tr("VLine");
    item.m_value=QFrame::VLine;
    items.append(item);

    item.m_text=tr("WinPanel");
    item.m_value=QFrame::WinPanel;
    items.append(item);

    pro->setProperty("items",QVariant::fromValue<ComboItems>(items));
    insertProperty(pro);

    pro = new QEnumProperty();
    pro->setName("frameShadow");
    pro->setShowName(tr("FrameShadow"));
    pro->setGroup("Attributes");

    items.clear();

    item.m_text=tr("Plain");
    item.m_value=QFrame::Plain;
    items.append(item);

    item.m_text=tr("Raised");
    item.m_value=QFrame::Raised;
    items.append(item);

    item.m_text=tr("Sunken");
    item.m_value=QFrame::Sunken;
    items.append(item);

    pro->setProperty("items",QVariant::fromValue<ComboItems>(items));
    insertProperty(pro);
}

QWidgetHostInfo* QFrameHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo();
    info->m_metaObject = &(QFrameHost::staticMetaObject);
    info->m_index = 2;
    info->m_showGroup = tr("Containners");
    info->m_showIcon = ":/inner/images/widgets/frame.png";
    info->m_showName = tr("Frame");
    info->m_name = "frame";
    return info;
}

int QFrameHost::getFrameShadow()
{
    return getPropertyValue("frameShadow").toInt();
}

void QFrameHost::setFrameShadow(int frameShadow)
{
    setPropertyValue("frameShadow",frameShadow);
}

int QFrameHost::getFrameShape()
{
    return getPropertyValue("frameShape").toInt();
}

void QFrameHost::setFrameShape(int frameShape)
{
    setPropertyValue("frameShape",frameShape);
}
