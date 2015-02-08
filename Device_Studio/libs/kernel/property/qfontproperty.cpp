#include "qfontproperty.h"

#include "qenumproperty.h"
#include "qintproperty.h"
#include "qboolproperty.h"

#include "../qvarianttype.h"
#include "../xmlnode.h"

#include <QFontDatabase>
#include <QTextOption>
#include <QPainter>

QFontProperty::QFontProperty(QAbstractProperty * parent):
    QAbstractProperty(parent)
{

    static QFontDatabase    fontDatabase;

    m_family=new QEnumProperty(this);
    m_family->setShowName(tr("Family"));
    m_family->setName("family");
    QStringList list=fontDatabase.families();
    tagComboItem item;
    ComboItems  items;
    foreach(QString str,list)
    {
        item.m_text=str;
        item.m_value=str;
        items.append(item);
    }
    m_family->setProperty("items",QVariant::fromValue<ComboItems>(items));


    m_pointSize=new QIntProperty(this);
    m_pointSize->setShowName(tr("Size"));
    m_pointSize->setName("size");

    m_bold=new QBoolProperty(this);
    m_bold->setShowName(tr("Bold"));
    m_bold->setName("bold");


    m_italic=new QBoolProperty(this);
    m_italic->setShowName(tr("Italic"));
    m_italic->setName("italic");

    m_underline=new QBoolProperty(this);
    m_underline->setShowName(tr("Underline"));
    m_underline->setName("underline");

    m_strikeout=new QBoolProperty(this);
    m_strikeout->setShowName(tr("Strikeout"));
    m_strikeout->setName("strikeout");
}

QString QFontProperty::getValueText()
{
    QFont f=getValue().value<QFont>();
    return f.family();
}

QIcon QFontProperty::getValueIcon()
{
    QFont f=getValue().value<QFont>();
    QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);
    QPainter p(&img);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setRenderHint(QPainter::Antialiasing, true);
    f.setPointSize(13);
    p.setFont(f);
    QTextOption t;
    t.setAlignment(Qt::AlignCenter);
    p.drawText(QRect(0, 0, 16, 16), QString(QLatin1Char('A')), t);
    return QPixmap::fromImage(img);
}

void QFontProperty::setValue(const QVariant &value)
{
    QFont f = value.value<QFont>();

    m_family->setValue(f.family());
    m_bold->setValue(f.bold());
    m_underline->setValue(f.underline());
    m_pointSize->setValue(f.pointSize());
    m_italic->setValue(f.italic());
    m_strikeout->setValue(f.strikeOut());
}

void QFontProperty::makeValue(XmlNode *xml)
{
    setName(xml->getProperty("name"));
}

void QFontProperty::writeValue(XmlNode *xml)
{
    xml->setProperty("name",getName());
}
