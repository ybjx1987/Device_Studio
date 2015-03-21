#ifndef QURLSHEETTYPEEDITOR_H
#define QURLSHEETTYPEEDITOR_H

#include "qabstractsheetpropertyeditor.h"

class QImageEditor;

class QUrlSheetTypeEditor : public QAbstractSheetPropertyEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QUrlSheetTypeEditor(QAbstractSheetType * property,QWidget* parent = NULL);
    ~QUrlSheetTypeEditor();
protected:
    void propertyChanged();
protected slots:
    void valueChanged(const QString & value);
protected:
    QImageEditor    *m_imageEditor;
};

#endif // QURLSHEETTYPEEDITOR_H
