#include "qabstractwidgethost.h"

#include "../property/qrectproperty.h"
#include "../property/qintproperty.h"
#include "../property/qboolproperty.h"
#include "../property/qenumproperty.h"
#include "../property/qintproperty.h"
#include "../property/qcursorproperty.h"
#include "../property/qmemerydataproperty.h"
#include "../property/qfontproperty.h"
#include "../property/qstringproperty.h"
#include "../property/qscriptproperty.h"
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

    QAbstractProperty * pro;

    pro = new QRectProperty();
    pro->setName("geometry");
    pro->setShowName(tr("Geometry"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QBoolProperty();
    pro->setName("enabled");
    pro->setShowName(tr("Enabled"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QIntProperty();
    pro->setName("level");
    pro->setShowName(tr("Level"));
    pro->setGroup("Attributes");
    pro->setValue(1);
    insertProperty(pro);

    pro = new QStringProperty();
    pro->setName("toolTip");
    pro->setShowName(tr("ToolTip"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QCursorProperty();
    pro->setName("cursor");
    pro->setShowName(tr("Cursor"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QEnumProperty();
    pro->setName("focusPolicy");
    pro->setShowName(tr("FocusPolicy"));
    pro->setGroup("Attributes");
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
    pro->setProperty("items",QVariant::fromValue<ComboItems>(items));
    insertProperty(pro);

    pro = new QFontProperty();
    pro->setName("font");
    pro->setShowName(tr("Font"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QMemeryDataProperty();
    pro->setName("memery");
    pro->setShowName(tr("Data Sync"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QScriptProperty();
    pro->setName("mousePress");
    pro->setShowName(tr("MousePress"));
    pro->setGroup("Events");
    insertProperty(pro);

    pro = new QScriptProperty();
    pro->setName("mouseMove");
    pro->setShowName(tr("MouseMove"));
    pro->setGroup("Events");
    insertProperty(pro);

    pro = new QScriptProperty();
    pro->setName("mouseRelease");
    pro->setShowName(tr("MouseRelease"));
    pro->setGroup("Events");
    insertProperty(pro);

    pro = new QScriptProperty();
    pro->setName("doubleClick");
    pro->setShowName(tr("DoubleClick"));
    pro->setGroup("Events");
    insertProperty(pro);
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

int QAbstractWidgetHost::getFocusPolicy()
{
    return getPropertyValue("focusPolicy").toInt();
}

void QAbstractWidgetHost::setFocusPolicy(int focusPolicy)
{
    setPropertyValue("focusPolicy",focusPolicy);
}

void QAbstractWidgetHost::setFontSize(int pointSize)
{
    setPropertyValue("font.size",pointSize);
}

int QAbstractWidgetHost::getFontSize()
{
    return getPropertyValue("font.size").toInt();
}

void QAbstractWidgetHost::setFontFamily(const QString &family)
{
    setPropertyValue("font.family",family);
}

QString QAbstractWidgetHost::getFontFamily()
{
    return getPropertyValue("font.family").toString();
}

void QAbstractWidgetHost::setFontBold(bool bold)
{
    setPropertyValue("font.bold",bold);
}

bool QAbstractWidgetHost::getFontBold()
{
    return getPropertyValue("font.bold").toBool();
}

void QAbstractWidgetHost::setFontUnderline(bool underline)
{
    setPropertyValue("font.underline",underline);
}

bool QAbstractWidgetHost::getFontUnderline()
{
    return getPropertyValue("font.underline").toBool();
}

void QAbstractWidgetHost::setFontItalic(bool italic)
{
    setPropertyValue("font.italic",italic);
}

bool QAbstractWidgetHost::getFontItalic()
{
    return getPropertyValue("font.italic").toBool();
}

void QAbstractWidgetHost::setFontStrikeout(bool strikeout)
{
    setPropertyValue("font.strikeout",strikeout);
}

bool QAbstractWidgetHost::getFontStrikeout()
{
    return getPropertyValue("font.strikeout").toBool();
}
