#ifndef QITEMENDWIDGET_H
#define QITEMENDWIDGET_H

#include <QWidget>

class QItemEndWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QItemEndWidget(QWidget *parent = 0);
    ~QItemEndWidget();
protected:
    void    paintEvent(QPaintEvent *);
signals:

public slots:
};

#endif // QITEMENDWIDGET_H
