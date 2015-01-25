#ifndef MINISPLITTER_H
#define MINISPLITTER_H

#include "platformlibglobal.h"

#include <QSplitter>

class PLATFORM_EXPORT MiniSplitter : public QSplitter
{
    Q_OBJECT
public:
    MiniSplitter(QWidget *parent = 0);
    MiniSplitter(Qt::Orientation orientation);

protected:
    QSplitterHandle *createHandle();
};

#endif // MINISPLITTER_H
