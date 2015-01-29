#ifndef QCOMMONEDITOR_H
#define QCOMMONEDITOR_H

#include "../platformlibglobal.h"

#include <QWidget>
#include <QLabel>

class QAbstractProperty;

class PLATFORM_EXPORT QCommonEditor : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE QCommonEditor(QAbstractProperty *property,QWidget *parent = 0);
protected slots:
    void    propertyChanged();
protected:
    QLabel      *m_icon;
    QLabel      *m_text;
    QAbstractProperty *m_property;
};

#endif // QCOMMONEDITOR_H
