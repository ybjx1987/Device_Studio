#ifndef QIMAGEEDITOR_H
#define QIMAGEEDITOR_H

#include "qabstractfileeditor.h"

class QImageView;

class QImageEditor : public QAbstractFileEditor
{
    Q_OBJECT
public:
    Q_INVOKABLE QImageEditor(QWidget *parent = 0);
    ~QImageEditor();

    static QStringList getSupportFile();

    void setResourceFile(QResourceFile *resource);
signals:

public slots:
protected:
    QImageView      *m_imageView;
};

#endif // QIMAGEEDITOR_H
