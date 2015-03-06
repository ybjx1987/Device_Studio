#ifndef QONEGROUPWIDGET_H
#define QONEGROUPWIDGET_H

#include <QWidget>

class QStyleSheetGroup;

class QOneGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QOneGroupWidget(QStyleSheetGroup * group,QWidget *parent = 0);
    ~QOneGroupWidget();

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *);
protected:
    QStyleSheetGroup    *m_group;
};

#endif // QONEGROUPWIDGET_H
