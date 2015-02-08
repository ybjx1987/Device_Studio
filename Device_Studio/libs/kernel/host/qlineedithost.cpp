#include "qlineedithost.h"

#include "../property/qbytearrayproperty.h"
#include "../property/qboolproperty.h"
#include "../property/qalignmentproperty.h"
#include "../property/qscriptproperty.h"

#include <QLineEdit>

QLineEditHost::QLineEditHost(QAbstractWidgetHost * parent):
    QWidgetHost(parent)
{
    setProperty("needFrame",false);
    setProperty("acceptDrop",false);
}

void QLineEditHost::createObject()
{
    m_object = new QLineEdit();
    m_object->setObjectName("lineedit");
    m_object->setProperty("geometry",QRect(0,0,100,20));
}

void QLineEditHost::initProperty()
{
    QWidgetHost::initProperty();

    removeProperty("mousePress");
    removeProperty("mouseMove");
    removeProperty("mouseRelease");
    removeProperty("doubleClick");

    QAbstractProperty * pro;

    pro = new QByteArrayProperty();
    pro->setName("text");
    pro->setShowName(tr("Text"));
    pro->setGroup("Attributes");
    pro->setCanSame(true);
    insertProperty(pro,2);

    pro = new QAlignmentProperty();
    pro->setName("alignment");
    pro->setShowName(tr("Alignment"));
    pro->setGroup("Attributes");
    pro->setCanSame(true);
    insertProperty(pro);

    pro = new QBoolProperty();
    pro->setName("readOnly");
    pro->setShowName(tr("ReadOnly"));
    pro->setGroup("Attributes");
    pro->setCanSame(true);
    insertProperty(pro);

    pro = new QBoolProperty();
    pro->setName("frame");
    pro->setShowName(tr("Frame"));
    pro->setGroup("Attributes");
    pro->setCanSame(true);
    insertProperty(pro);

    pro = new QScriptProperty();
    pro->setName("textChanged");
    pro->setShowName(tr("TextChanged"));
    pro->setGroup("Events");
    insertProperty(pro);

    pro = new QScriptProperty();
    pro->setName("editFinish");
    pro->setShowName(tr("EditFinish"));
    pro->setGroup("Events");
    insertProperty(pro);
}

QString QLineEditHost::getText()
{
    return getPropertyValue("text").toString();
}

void QLineEditHost::setText(const QString &text)
{
    setPropertyValue("text",text);
}

void QLineEditHost::setAlignment(int alignment)
{
    setPropertyValue("alignment",alignment);
}

int QLineEditHost::getAlignment()
{
    return getPropertyValue("alignment").toInt();
}

void QLineEditHost::setFrame(bool frame)
{
    setPropertyValue("frame",frame);
}

bool QLineEditHost::getFrame()
{
    return getPropertyValue("frame").toBool();
}

void QLineEditHost::setReadOnly(bool readOnly)
{
    setPropertyValue("readOnly",readOnly);
}

bool QLineEditHost::getReadOnly()
{
    return getPropertyValue("readOnly").toBool();
}

QWidgetHostInfo* QLineEditHost::getHostInfo()
{
    QWidgetHostInfo * info = new QWidgetHostInfo();
    info->m_metaObject = &(QLineEditHost::staticMetaObject);
    info->m_index = 10;
    info->m_showGroup = tr("Input Widgets");
    info->m_showIcon = ":/inner/images/widgets/lineedit.png";
    info->m_showName = tr("LineEdit");
    info->m_name = "lineedit";
    return info;
}
