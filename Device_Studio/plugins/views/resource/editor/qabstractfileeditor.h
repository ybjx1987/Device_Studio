#ifndef QABSTRACTFILEEDITOR_H
#define QABSTRACTFILEEDITOR_H

#include <QWidget>
#include <QAction>

class QResourceFile;

class QAbstractFileEditor : public QWidget
{
    Q_OBJECT
public:
    explicit QAbstractFileEditor(QWidget *parent = 0);
    ~QAbstractFileEditor();

    virtual void setResourceFile(QResourceFile * resource);

    virtual QList<QAction*>     getToolBarActions();
protected:
    QResourceFile       *m_resource;
};

#endif // QABSTRACTFILEEDITOR_H
