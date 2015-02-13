#ifndef QVALIDATOREDIT_H
#define QVALIDATOREDIT_H

#include <QLineEdit>

class QEditValidator;

class QValidatorEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QString textValue READ value WRITE setValue USER true)
public:
    QValidatorEdit(const QString &reg="[_a-zA-Z][_a-zA-Z0-9]{,64}",QWidget* parent=0);

    QString value() const;

    void    setIntermediateList(QStringList list);
    void    markIntermediateState();
public slots:
    void setValue(const QString & text);
private slots:
    void slotTextChanged(const QString &text);
protected:
    QString     m_text;
    QEditValidator  *m_validator;
};

#endif // QVALIDATOREDIT_H
