#include "qprojecthost.h"

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
}

void QProjectHost::initProperty()
{

}
