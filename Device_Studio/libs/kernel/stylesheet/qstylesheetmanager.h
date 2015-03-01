#ifndef QSTYLESHEETMANAGER_H
#define QSTYLESHEETMANAGER_H

#include <QObject>

class QStyleSheetManager : public QObject
{
    Q_OBJECT
public:
    explicit QStyleSheetManager(QObject *parent = 0);
    ~QStyleSheetManager();

signals:

public slots:
};

#endif // QSTYLESHEETMANAGER_H
