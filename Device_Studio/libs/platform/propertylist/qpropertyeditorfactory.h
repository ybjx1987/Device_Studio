#ifndef QPROPERTYEDITORFACTORY_H
#define QPROPERTYEDITORFACTORY_H

#include "../platformlibglobal.h"

#include <QMetaObject>
#include <QString>
#include <QMap>

class QAbstractPropertyEditor;
class QAbstractProperty;

class PLATFORM_EXPORT QPropertyEditorFactory
{
protected:
    QPropertyEditorFactory(){}

public:
    static void registerEditor(const QString &className,const QMetaObject &metaObject);

    static QAbstractPropertyEditor* createEditor(const QString &className,
                                                 QAbstractProperty* property);
    static void registerInnerEditor();
protected:
    static QMap<QString,QMetaObject>   m_metaObjects;
};

#endif // QPROPERTYEDITORFACTORY_H
