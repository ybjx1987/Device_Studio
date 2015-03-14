#ifndef QTITLEWIDGET_H
#define QTITLEWIDGET_H

#include <QWidget>
#include <QMap>

class QSingleTitleWidget;
class QToolBarButton;

class QTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QTitleWidget(QWidget *parent = 0);
    ~QTitleWidget();

    void    addTitle(const QString & title);
    void    removeTitle(const QString & title);

    void    clear();
protected:
    void    paintEvent(QPaintEvent *);
signals:
    void    delTitle(const QString & title);
    void    addTitle();
    void    delItem();
protected slots:
    void    titleDeled();
protected:
    QList<QSingleTitleWidget*>  m_titles;
    QMap<QString,QSingleTitleWidget*>   m_textToTitle;
    QToolBarButton              *m_delButton;
    QToolBarButton              *m_addTitleButton;
};

#endif // QTITLEWIDGET_H
