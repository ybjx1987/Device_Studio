#ifndef QABSTACTPROPERTYEDITOR_H
#define QABSTACTPROPERTYEDITOR_H

#include "../../platformlibglobal.h"

#include <QWidget>

class QAbstractProperty;

class PLATFORM_EXPORT QAbstractPropertyEditor : public QWidget
{
    Q_OBJECT
public:
    explicit QAbstractPropertyEditor(QAbstractProperty * property,QWidget *parent = 0);
    ~QAbstractPropertyEditor();
protected slots:
    virtual void propertyValueChanged();
signals:
    void    valueChanged(const QVariant &value);
protected:
    QAbstractProperty   *m_property;
};

#endif // QABSTACTPROPERTYEDITOR_H
