#include "qcursorproperty.h"

#include "../qvarianttype.h"
#include "../xmlnode.h"

#include <QCursor>
#include <QIcon>

QCursorProperty::QCursorProperty(QAbstractProperty * parent):
    QEnumProperty(parent)
{
    setType("Cursor");
    ComboItems items;
    tagComboItem item;
    item.m_icon=":/inner/images/cursors/arrow.png";
    item.m_text=tr("Arrow");
    item.m_value=QCursor(Qt::ArrowCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/uparrow.png";
    item.m_text=tr("Up Arrow");
    item.m_value=QCursor(Qt::UpArrowCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/cross.png";
    item.m_text=tr("Cross");
    item.m_value=QCursor(Qt::CrossCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/wait.png";
    item.m_text=tr("Wait");
    item.m_value=QCursor(Qt::WaitCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/ibeam.png";
    item.m_text=tr("IBeam");
    item.m_value=QCursor(Qt::IBeamCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/sizev.png";
    item.m_text=tr("Size Vertical");
    item.m_value=QCursor(Qt::SizeVerCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/sizeh.png";
    item.m_text=tr("Size Horizontal");
    item.m_value=QCursor(Qt::SizeHorCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/sizef.png";
    item.m_text=tr("Size Slash");
    item.m_value=QCursor(Qt::SizeFDiagCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/sizeb.png";
    item.m_text=tr("Size Backslash");
    item.m_value=QCursor(Qt::SizeBDiagCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/sizeall.png";
    item.m_text=tr("Size All");
    item.m_value=QCursor(Qt::SizeAllCursor);
    items.append(item);

    item.m_icon="";
    item.m_text=tr("Blank");
    item.m_value=QCursor(Qt::BlankCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/vsplit.png";
    item.m_text=tr("Split Vertical");
    item.m_value=QCursor(Qt::SplitVCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/hsplit.png";
    item.m_text=tr("Split Horizontal");
    item.m_value=QCursor(Qt::SplitHCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/hand.png";
    item.m_text=tr("Pointing Hand");
    item.m_value=QCursor(Qt::PointingHandCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/no.png";
    item.m_text=tr("Forbidden");
    item.m_value=QCursor(Qt::ForbiddenCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/openhand.png";
    item.m_text=tr("Open Hand");
    item.m_value=QCursor(Qt::OpenHandCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/closedhand.png";
    item.m_text=tr("Closed Hand");
    item.m_value=QCursor(Qt::ClosedHandCursor);
    items.append(item);

    item.m_icon=":/inner/images/cursors/whatsthis.png";
    item.m_text=tr("What's This");
    item.m_value=QCursor(Qt::WhatsThisCursor);
    items.append(item);

    item.m_icon=":/inner/inner/images/cursors/busy.png";
    item.m_text=tr("Busy");
    item.m_value=QCursor(Qt::BusyCursor);
    items.append(item);

    setProperty("items",QVariant::fromValue<ComboItems>(items));
}

void QCursorProperty::makeValue(XmlNode *xml)
{
    setName(xml->getProperty("name"));
    setType(xml->getProperty("type"));
    QCursor c((Qt::CursorShape)xml->getProperty("value").toInt());
    setValue(QVariant::fromValue<QCursor>(c));

}

void QCursorProperty::writeValue(XmlNode *xml)
{
    xml->setProperty("name",getName());
    xml->setProperty("type",getType());
    QCursor c=getValue().value<QCursor>();
    xml->setProperty("value",QString::number(c.shape()));
}
