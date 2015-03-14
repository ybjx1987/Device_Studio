#ifndef QRESOURCEITEMWIDGET_H
#define QRESOURCEITEMWIDGET_H

#include <QWidget>
#include <QLabel>

class ResourceFileInfo;

class QToolBarButton;

class QResourceItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QResourceItemWidget(ResourceFileInfo *info,QWidget *parent = 0);
    ~QResourceItemWidget();
    ResourceFileInfo *getInfo();
    void    setText(const QString & text);
    QString getText();
protected:
    void    enterEvent(QEvent *);
    void    leaveEvent(QEvent *);
signals:
    void    rename();
    void    remove();
protected:
    QLabel      *m_textLabel;
    ResourceFileInfo    *m_info;
    QToolBarButton  *m_renameButton;
    QToolBarButton  *m_removeButton;
};

#endif // QRESOURCEITEMWIDGET_H
