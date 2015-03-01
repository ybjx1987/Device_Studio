#ifndef QSINGLETITLEWIDGET_H
#define QSINGLETITLEWIDGET_H

#include <QWidget>
#include <QLabel>

class QToolBarButton;

class QSingleTitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QSingleTitleWidget(QWidget *parent = 0);
    ~QSingleTitleWidget();

    void    setText(const QString & title);
protected:
    void updateWidth();
signals:
    void    remove();
protected:
    QLabel  *m_text;
    QToolBarButton * m_deleteButton;
};

#endif // QSINGLETITLEWIDGET_H
