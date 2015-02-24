#include "qintdatahost.h"

QIntDataHost::QIntDataHost(QAbstractHost * parent):
    QAbstractDataHost(parent)
{

}

QAbstractHostInfo * QIntDataHost::getHostInfo()
{
    QDataHostInfo * info = new QDataHostInfo;
    info->m_name = "dataNumber";
    info->m_showName = "Number";
    info->m_metaObject = &(QIntDataHost::staticMetaObject);
    return info;
}

