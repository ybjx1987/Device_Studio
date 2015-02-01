#include "qabstractwidgethost.h"

#include "../property/qrectproperty.h"
#include "../property/qintproperty.h"
#include "../property/qboolproperty.h"
#include "../property/qenumproperty.h"
#include "../property/qintproperty.h"
#include "../property/qcursorproperty.h"
#include "../qvarianttype.h"

#include <QWidget>

QAbstractWidgetHost::QAbstractWidgetHost(QAbstractWidgetHost *parent):
    QAbstractHost(parent)
{

}

void QAbstractWidgetHost::initProperty()
{
    QAbstractHost::initProperty();
    QWidget * wid = (QWidget*)m_object;

    wid->setMouseTracking(true);

    QRectProperty * rectPro;
    rectPro = new QRectProperty();
    rectPro->setName("geometry");
    rectPro->setShowName(tr("Geometry"));
    rectPro->setGroup("Attributes");
    rectPro->setCanSame(true);
    rectPro->setDefaultValue(QRect(0,0,100,70));
    insertProperty(rectPro);

    QBoolProperty  *boolPro;
    boolPro = new QBoolProperty();
    boolPro->setName("enabled");
    boolPro->setShowName(tr("Enabled"));
    boolPro->setGroup("Attributes");
    boolPro->setCanSame(true);
    insertProperty(boolPro);

    QIntProperty *intPro;
    intPro = new QIntProperty();
    intPro->setName("level");
    intPro->setShowName(tr("Level"));
    intPro->setGroup("Attributes");
    intPro->setValue(1);
    insertProperty(intPro);

    QCursorProperty * cursorPro = new QCursorProperty();
    cursorPro->setName("cursor");
    cursorPro->setShowName(tr("Cursor"));
    cursorPro->setGroup("Attributes");
    cursorPro->setCanSame(true);
    cursorPro->setValue(QVariant::fromValue<QCursor>(QCursor(Qt::ArrowCursor)));
    insertProperty(cursorPro);

    QEnumProperty *enumPro;
    enumPro = new QEnumProperty();
    enumPro->setName("focusPolicy");
    enumPro->setShowName(tr("FocusPolicy"));
    enumPro->setGroup("Attributes");
    enumPro->setCanSame(true);
    ComboItems items;
    tagComboItem item;
    item.m_text="TabFocus";
    item.m_value=Qt::TabFocus;
    items.append(item);
    item.m_text="ClickFocus";
    item.m_value=Qt::ClickFocus;
    items.append(item);
    item.m_text="StrongFocus";
    item.m_value=Qt::StrongFocus;
    items.append(item);
    item.m_text="WheelFocus";
    item.m_value=Qt::WheelFocus;
    items.append(item);
    item.m_text="NoFocus";
    item.m_value=Qt::NoFocus;
    items.append(item);
    enumPro->setProperty("items",QVariant::fromValue<ComboItems>(items));
    enumPro->setValue(Qt::NoFocus);
    insertProperty(enumPro);
}

void QAbstractWidgetHost::setGeometry(int x, int y, int width, int height)
{
    QRect rect(x,y,width,height);
    setPropertyValue("geometry",rect);
}

void QAbstractWidgetHost::setEnabled(bool enabled)
{
    setPropertyValue("enabled",enabled);
}

void QAbstractWidgetHost::setToolTip(const QString &tooltip)
{
    setPropertyValue("toolTip",tooltip);
}

int QAbstractWidgetHost::getX()
{
    return getPropertyValue("geometry").toRect().x();
}

int QAbstractWidgetHost::getY()
{
    return getPropertyValue("geometry").toRect().y();
}

int QAbstractWidgetHost::getWidth()
{
    return getPropertyValue("geometry").toRect().width();
}

int QAbstractWidgetHost::getHeight()
{
    return getPropertyValue("geometry").toRect().height();
}

bool QAbstractWidgetHost::getEnabled()
{
    return getPropertyValue("enabled").toBool();
}

QString QAbstractWidgetHost::getToolTip()
{
    return getPropertyValue("toolTip").toString();
}

void QAbstractWidgetHost::setCursor(int cursor)
{
    QCursor c((Qt::CursorShape)cursor);
    setPropertyValue("cursor",QVariant::fromValue<QCursor>(c));
}

int QAbstractWidgetHost::getCursor()
{
    QCursor c=getPropertyValue("cursor").value<QCursor>();
    return c.shape();
}

int QAbstractWidgetHost::getLevel()
{
    return getPropertyValue("level").toInt();
}

void QAbstractWidgetHost::setLevel(int level)
{
    setPropertyValue("level",level);
}
