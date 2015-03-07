#ifndef QLENGTHSHEETTYPEEDITOR_H
#define QLENGTHSHEETTYPEEDITOR_H

#include "qnumbersheettypeeditor.h"

class QLengthSheetTypeEditor : public QNumberSheetTypeEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QLengthSheetTypeEditor(QAbstractSheetType * property,
                                       QWidget * parent = NULL);
    ~QLengthSheetTypeEditor();
};

#endif // QLENGTHSHEETTYPEEDITOR_H
