#ifndef QBRUSHSHEETTYPEEDITOR_H
#define QBRUSHSHEETTYPEEDITOR_H

#include "qabstractsheetpropertyeditor.h"

class QBrushEditor;

class QBrushSheetTypeEditor : public QAbstractSheetPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QBrushSheetTypeEditor(QAbstractSheetType * property,
                         QWidget * parent = NULL);
    ~QBrushSheetTypeEditor();
protected:
    void    propertyChanged();
protected slots:
    void    valueChanged(const QVariant & value);
protected:
    QBrushEditor        *m_brushEditor;
};

#endif // QBRUSHSHEETTYPEEDITOR_H
