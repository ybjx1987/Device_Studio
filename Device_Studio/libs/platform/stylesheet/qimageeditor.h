#ifndef QIMAGEEDITOR_H
#define QIMAGEEDITOR_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>

class QAbstractSheetType;

class QImageEditor : public QWidget
{
    Q_OBJECT
public:
    explicit QImageEditor(QAbstractSheetType * property,QWidget *parent = 0);
    ~QImageEditor();

protected:
    void updateValue();
signals:
    void valueChanged(const QString & value);
protected slots:
    void editImage();
protected:
    QLabel  *m_iconLabel;
    QLabel  *m_textLabel;
    QToolButton *m_editButton;
    QAbstractSheetType  *m_property;
};

#endif // QIMAGEEDITOR_H
