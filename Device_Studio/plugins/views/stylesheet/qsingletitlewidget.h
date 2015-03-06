#ifndef QSINGLETITLEWIDGET_H
#define QSINGLETITLEWIDGET_H

#include <QWidget>
#include <QLabel>

class QToolBarButton;

class QSingleTitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QSingleTitleWidget(const QString & title,QWidget *parent = 0);
    ~QSingleTitleWidget();
    QString text();
protected:
    void updateWidth();
    void paintEvent(QPaintEvent *);
signals:
    void    remove();
protected:
    QLabel  *m_text;
    QToolBarButton * m_deleteButton;
};

#endif // QSINGLETITLEWIDGET_H
