#ifndef QABSTRACTSTYLESHEETPROPERTYEDITOR_H
#define QABSTRACTSTYLESHEETPROPERTYEDITOR_H

#include <QWidget>

class QAbstractSheetType;

class QAbstractStyleSheetPropertyEditor : public QWidget
{
    Q_OBJECT
public:
    explicit QAbstractStyleSheetPropertyEditor(
            QAbstractSheetType * property,QWidget *parent = 0);
    ~QAbstractStyleSheetPropertyEditor();

signals:

public slots:

protected:
    QAbstractSheetType  *m_property;
};

#endif // QABSTRACTSTYLESHEETPROPERTYEDITOR_H
