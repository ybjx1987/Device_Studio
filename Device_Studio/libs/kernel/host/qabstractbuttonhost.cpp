#include "qabstractbuttonhost.h"

#include "../property/qstringproperty.h"
#include "../property/qboolproperty.h"
#include "../property/qscriptproperty.h"

QAbstractButtonHost::QAbstractButtonHost(QAbstractWidgetHost * parent):
    QWidgetHost(parent)
{
    setProperty("needFrame",false);
    setProperty("acceptDrop",false);
    setProperty("editProperty","text");
}

void QAbstractButtonHost::initProperty()
{
    QAbstractProperty * pro;

    QWidgetHost::initProperty();

    pro = new QStringProperty();
    pro->setName("text");
    pro->setShowName(tr("Text"));
    pro->setGroup("Attributes");
    insertProperty(pro,1);

    pro = new QBoolProperty();
    pro->setName("checkable");
    pro->setShowName(tr("Checkable"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QBoolProperty();
    pro->setName("checked");
    pro->setShowName(tr("Checked"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QScriptProperty();
    pro->setName("clicked");
    pro->setShowName(tr("Clicked"));
    pro->setGroup("Events");
    insertProperty(pro);
}

void QAbstractButtonHost::setText(const QString &text)
{
    setPropertyValue("text",text);
}

QString QAbstractButtonHost::getText()
{
    return getPropertyValue("text").toString();
}

void QAbstractButtonHost::setCheckable(bool checkable)
{
    setPropertyValue("checkable",checkable);
}

bool QAbstractButtonHost::getCheckable()
{
    return getPropertyValue("checkable").toBool();
}

void QAbstractButtonHost::setChecked(bool checked)
{
    setPropertyValue("checked",checked);
}

bool QAbstractButtonHost::getChecked()
{
    return getPropertyValue("checked").toBool();
}
