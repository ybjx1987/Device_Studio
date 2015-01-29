#ifndef QPROPERTYEDITORPANE_H
#define QPROPERTYEDITORPANE_H

#include <QWidget>
#include <QToolButton>

class QAbstractProperty;

class QPropertyEditorPane : public QWidget
{
    Q_OBJECT
public:
    explicit QPropertyEditorPane(QAbstractProperty * property,QWidget *parent = 0);
protected:
    void        paintEvent(QPaintEvent *);
    bool        eventFilter(QObject *, QEvent *);
protected slots:
    void    propertyRefresh();
protected:
    QToolButton                 *m_resetButton;
    QAbstractProperty           *m_property;
    QWidget                     *m_widget;
};

#endif // QPROPERTYEDITORPANE_H
