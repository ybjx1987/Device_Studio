#ifndef QFONTSHEETTYPEEDITOR_H
#define QFONTSHEETTYPEEDITOR_H

#include "qabstractsheetpropertyeditor.h"

#include <QComboBox>
#include <QSpinBox>

class QFontSheetTypeEditor : public QAbstractSheetPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QFontSheetTypeEditor(QAbstractSheetType * property,
                         QWidget * parent = NULL);
    ~QFontSheetTypeEditor();

protected:
    virtual void    propertyChanged();
protected slots:
    void            propertyEdited();
protected:
    QComboBox       *m_nameCombo;
    QComboBox       *m_styleCombo;
    QSpinBox        *m_sizeEditor;
};

#endif // QFONTSHEETTYPEEDITOR_H
