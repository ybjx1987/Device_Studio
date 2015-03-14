#ifndef QIMAGEEDITOR_H
#define QIMAGEEDITOR_H

#include "qabstractfileeditor.h"

class QImageEditor : public QAbstractFileEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QImageEditor(QWidget *parent = 0);
    ~QImageEditor();

    static QStringList getSupportFile();
signals:

public slots:
};

#endif // QIMAGEEDITOR_H
