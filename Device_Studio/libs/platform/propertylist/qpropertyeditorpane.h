#ifndef QPROPERTYEDITORPANE_H
#define QPROPERTYEDITORPANE_H

#include <QWidget>
#include <QToolButton>

class QAbstractProperty;
class QAbstractPropertyEditor;

class QPropertyEditorPane : public QWidget
{
    Q_OBJECT
public:
    explicit QPropertyEditorPane(QAbstractProperty * property,QWidget *parent = 0);
    ~QPropertyEditorPane();
protected:
    void        paintEvent(QPaintEvent *);
    bool        eventFilter(QObject *, QEvent *);
protected slots:
    void    propertyRefresh();
    void    propertyEdit(const QVariant & value);
signals:
    void    propertyValueEdit(QAbstractProperty * property,const QVariant &value);
protected:
    QToolButton                 *m_resetButton;
    QAbstractProperty           *m_property;
    QAbstractPropertyEditor     *m_widget;
};

#endif // QPROPERTYEDITORPANE_H
