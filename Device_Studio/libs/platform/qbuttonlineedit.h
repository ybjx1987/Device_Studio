#ifndef QBUTTONLINEEDIT_H
#define QBUTTONLINEEDIT_H

#include "platformlibglobal.h"

#include <QLineEdit>
#include <QPushButton>

class PLATFORM_EXPORT QButtonLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit QButtonLineEdit(QWidget *parent = 0);
    ~QButtonLineEdit();
protected:
    void    resizeEvent(QResizeEvent *);
protected slots:
    void    showDialog();
signals:

public slots:
protected:
    QPushButton     *m_button;
};

#endif // QBUTTONLINEEDIT_H
