#ifndef QSHEETTYPEEDITORFACTORY_H
#define QSHEETTYPEEDITORFACTORY_H

#include <QMap>
#include <QMetaObject>

class QAbstractSheetType;
class QAbstractSheetPropertyEditor;

class QSheetTypeEditorFactory
{
protected:
    QSheetTypeEditorFactory();
public:
    static void registerEditor(const QString & name,QMetaObject meta);
    static QAbstractSheetPropertyEditor * create(const QString & name,
                                   QAbstractSheetType * property);
    static void registerInnerEditor();
protected:
    static QMap<QString,QMetaObject>   m_nameToMeta;

};

#endif // QSHEETTYPEEDITORFACTORY_H
