#ifndef QBRUSHEDITOR_H
#define QBRUSHEDITOR_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QVariant>

class QAbstractSheetType;

class QBrushEditor : public QWidget
{
    Q_OBJECT
public:
    explicit QBrushEditor(QAbstractSheetType * property,QWidget *parent = 0);
    ~QBrushEditor();
    void    updateValue();
signals:
    void    valueChanged(const QVariant & value);
protected slots:
    void    editColor();
    void    editGradient();
protected:
    QLabel  *m_iconLabel;
    QLabel  *m_textLabel;
    QToolButton *m_editButton;
    QAbstractSheetType  *m_property;
};

#endif // QBRUSHEDITOR_H
