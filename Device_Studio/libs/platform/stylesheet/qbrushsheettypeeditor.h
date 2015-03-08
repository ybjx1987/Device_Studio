#ifndef QBRUSHSHEETTYPEEDITOR_H
#define QBRUSHSHEETTYPEEDITOR_H

#include "qabstractsheetpropertyeditor.h"

#include <QComboBox>
#include <QToolButton>
#include <QLabel>

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
    void    editColor();
    void    editGradient();
protected:
    QLabel  *m_iconLabel;
    QLabel  *m_textLabel;
    QToolButton *m_editButton;
};

#endif // QBRUSHSHEETTYPEEDITOR_H
