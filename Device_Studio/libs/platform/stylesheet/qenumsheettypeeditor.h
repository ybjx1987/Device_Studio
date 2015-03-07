#ifndef QENUMSHEETTYPEEDITOR_H
#define QENUMSHEETTYPEEDITOR_H

#include "qabstractsheetpropertyeditor.h"

#include <QComboBox>

class QEnumSheetTypeEditor : public QAbstractSheetPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QEnumSheetTypeEditor(QAbstractSheetType * property,
                         QWidget * parent = NULL);
    ~QEnumSheetTypeEditor();
protected:
    void    propertyChanged();
protected slots:
    void    propertyEdited();
protected:
    QComboBox   *m_combo;
};

#endif // QENUMSHEETTYPEEDITOR_H
