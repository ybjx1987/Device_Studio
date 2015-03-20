#ifndef QBORDERSHEETTYPEEDITOR_H
#define QBORDERSHEETTYPEEDITOR_H

#include "qabstractsheetpropertyeditor.h"

#include <QSpinBox>
#include <QComboBox>

class QBrushEditor;

class QBorderSheetTypeEditor : public QAbstractSheetPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QBorderSheetTypeEditor(QAbstractSheetType * property,
                                       QWidget * parent = NULL);
    ~QBorderSheetTypeEditor();
protected slots:
    void    widthChanged();
    void    styleChanged();
    void    brushChanged(const QVariant & value);
protected:

    void    propertyChanged();
protected:
    QSpinBox        *m_borderWidth;
    QComboBox       *m_borderStyle;
    QBrushEditor    *m_brushEditor;
};

#endif // QBORDERSHEETTYPEEDITOR_H
