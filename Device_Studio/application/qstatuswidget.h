#ifndef QSTATUSWIDGET_H
#define QSTATUSWIDGET_H

#include <QWidget>

#include <QToolButton>
#include <QList>
#include <QTimeLine>
#include <QLabel>

class QStatusButton: public QToolButton
{
    Q_OBJECT
public:
    QStatusButton(int number,const QString &text,QWidget* parent=0);

    QSize sizeHint() const;

    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void flash(int count =3);
    void setIconBadgeNumber(int number);

    void checkStateSet();

protected:
    QString m_number;
    QString m_text;
    QTimeLine *m_flashTimer;
    QLabel      *m_label;
};


class QStatusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QStatusWidget(QWidget *parent = 0);

    void    setButtonEnabled(int index,bool enabled);
    void    setButtonChecked(int index,bool checked);
signals:
    void    clicked(int index,bool select);
protected slots:
    void    buttonClicked();
protected:
    QList<QStatusButton*>     m_buttons;

    int                       m_select;
};


#endif // QSTATUSWIDGET_H
