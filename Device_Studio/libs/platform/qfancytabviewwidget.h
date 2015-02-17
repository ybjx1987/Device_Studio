#ifndef QFANCYTABVIEWWIDGET_H
#define QFANCYTABVIEWWIDGET_H

#include <QLabel>

class QFancyTabViewWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float fader READ fader WRITE setFader)
public:
    explicit QFancyTabViewWidget(QWidget *parent = 0);
    ~QFancyTabViewWidget();

    float   fader();
    void    setFader(float fader);

    void    select(bool select);

    void    setIcon(const QString &icon);
    void    setText(const QString &text);

    QString getText();
protected:
    void    enterEvent(QEvent* e);
    void    leaveEvent(QEvent* e);
    void    mouseReleaseEvent(QMouseEvent*e);
    void    paintEvent(QPaintEvent *e);
signals:
    void    selected();
public slots:
protected:
    bool    m_select;
    float   m_fader;
    QLabel  *m_iconLabel;
    QLabel  *m_textLabel;
};

#endif // QFACNYTABVIEWWIDGET_H
