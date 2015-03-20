#ifndef QNUMBERSHEETTYPEEDITOR_H
#define QNUMBERSHEETTYPEEDITOR_H

#include "qabstractsheetpropertyeditor.h"

#include <QSpinBox>

class QNumberSheetTypeEditor : public QAbstractSheetPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QNumberSheetTypeEditor(QAbstractSheetType * property,
                                       QWidget * parent = NULL);
    ~QNumberSheetTypeEditor();
protected:

protected slots:
    void    valueEdited();
protected:
    QSpinBox        *m_valueEditor;
};

#endif // QNUMBERSHEETTYPEEDITOR_H
