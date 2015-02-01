#include "qabstractpage.h"

void QAbstractPage::initPlugin()
{
    createWidget();
    if(m_widget != NULL)
    {
        m_widget->setVisible(false);
    }
}

QWidget* QAbstractPage::getWidget()
{
    return m_widget;
}

QString QAbstractPage::getPluginType()
{
    return "Plugin.Page";
}

void QAbstractPage::createWidget()
{
    m_widget = NULL;
}

