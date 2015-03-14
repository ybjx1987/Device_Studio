#include "qsheettypeeditorfactory.h"

#include "qnumbersheettypeeditor.h"
#include "qenumsheettypeeditor.h"
#include "qfontsheettypeeditor.h"
#include "qbrushsheettypeeditor.h"
#include "qbordersheettypeeditor.h"

QMap<QString,QMetaObject> QSheetTypeEditorFactory::m_nameToMeta;

QSheetTypeEditorFactory::QSheetTypeEditorFactory()
{

}

void QSheetTypeEditorFactory::registerEditor(const QString &name, QMetaObject meta)
{
    if(m_nameToMeta.keys().contains(name))
    {
        return;
    }
    m_nameToMeta.insert(name,meta);
}

QAbstractSheetPropertyEditor * QSheetTypeEditorFactory::create(const QString &name, QAbstractSheetType *property)
{
    if(!m_nameToMeta.keys().contains(name))
    {
        return NULL;
    }
    QMetaObject meta = m_nameToMeta.value(name);

    QAbstractSheetPropertyEditor * editor = (QAbstractSheetPropertyEditor*)meta.newInstance(
                Q_ARG(QAbstractSheetType*,property));
    return editor;
}

void QSheetTypeEditorFactory::registerInnerEditor()
{
    registerEditor("QNumberSheetType",QNumberSheetTypeEditor::staticMetaObject);
    registerEditor("QEnumSheetType",QEnumSheetTypeEditor::staticMetaObject);
    registerEditor("QFontSheetType",QFontSheetTypeEditor::staticMetaObject);
    registerEditor("QBrushSheetType",QBrushSheetTypeEditor::staticMetaObject);
    registerEditor("QBorderSheetType",QBorderSheetTypeEditor::staticMetaObject);
}
