#ifndef QBORDERSHEETTYPEEDITOR_H
#define QBORDERSHEETTYPEEDITOR_H

#include "qbrushsheettypeeditor.h"

#include <QSpinBox>
#include <QComboBox>

class QBorderSheetTypeEditor : public QBrushSheetTypeEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QBorderSheetTypeEditor(QAbstractSheetType * property,
                                       QWidget * parent = NULL);
    ~QBorderSheetTypeEditor();
protected slots:
    void    widthChanged();
    void    styleChanged();
protected:
    QSpinBox        *m_borderWidth;
    QComboBox       *m_borderStyle;
};

#endif // QBORDERSHEETTYPEEDITOR_H
