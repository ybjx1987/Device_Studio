#ifndef QABSTRACTSHEETPROPERTYEDITOR_H
#define QABSTRACTSHEETPROPERTYEDITOR_H

#include <QWidget>

class QAbstractSheetType;

class QAbstractSheetPropertyEditor : public QWidget
{
    Q_OBJECT
public:
    explicit QAbstractSheetPropertyEditor(QAbstractSheetType * property,QWidget *parent = 0);
    ~QAbstractSheetPropertyEditor();

signals:

protected slots:
    virtual void    propertyChanged();

protected:
    void    paintEvent(QPaintEvent *);
protected:
    QAbstractSheetType  *m_property;
};

#endif // QABSTRACTSHEETPROPERTYEDITOR_H
