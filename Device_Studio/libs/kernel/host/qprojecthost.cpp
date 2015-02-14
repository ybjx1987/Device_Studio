#include "qprojecthost.h"

#include "../property/qbytearrayproperty.h"
#include "../property/qboolproperty.h"
#include "../property/qscriptproperty.h"
#include "../property/qrectproperty.h"
#include "../xmlnode.h"

#include <QFile>

QProjectHost::QProjectHost():
    QAbstractHost(NULL)
{

}

QProjectHost::~QProjectHost()
{

}

void QProjectHost::createObject()
{
    m_object = new QObject();
    m_object->setProperty("frame",false);
    m_object->setProperty("design-size",QRect(0,0,800,600));
    m_object->setProperty("running-size",QRect(0,0,800,600));
}

void QProjectHost::initProperty()
{
    QAbstractHost::initProperty();

    QAbstractProperty * pro;

    pro = getProperty("objectName");
    pro->setEditable(false);

    pro = new QByteArrayProperty;
    pro->setName("path");
    pro->setShowName(tr("Path"));
    pro->setGroup("Attributes");
    pro->setEditable(false);
    insertProperty(pro);

    pro = new QBoolProperty;
    pro->setName("frame");
    pro->setShowName(tr("Frae"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QRectProperty;
    pro->setName("design-size");
    ((QRectProperty*)pro)->setSizeType(true);
    pro->setShowName(tr("Design Size"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QRectProperty;
    pro->setName("running-size");
    ((QRectProperty*)pro)->setSizeType(true);
    pro->setShowName(tr("Running Size"));
    pro->setGroup("Attributes");
    insertProperty(pro);

    pro = new QScriptProperty;
    pro->setName("beforeStartup");
    pro->setShowName(tr("Before Startup"));
    pro->setGroup("Events");
    insertProperty(pro);

    pro = new QScriptProperty;
    pro->setName("afterClosed");
    pro->setShowName(tr("After Closed"));
    pro->setGroup("Events");
    insertProperty(pro);
}

bool QProjectHost::save(const QString &filename)
{
    QFile file(filename);

    if(!file.open(QFile::ReadWrite))
    {
        return false;
    }

    XmlNode node;

    toXml(&node);

    QString buffer;
    if(!node.save(buffer))
    {
        return false;
    }

    file.resize(0);
    file.write(buffer.toLocal8Bit());
    file.close();

    return true;
}
