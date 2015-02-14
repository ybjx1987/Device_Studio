#include "qvalidatoredit.h"

#include <QValidator>

class  QEditValidator: public QValidator
{
public:
    QEditValidator(const QString & reg="",QObject* parent=0);

    virtual State validate(QString &, int &) const;

    void    setList(QStringList list);
protected:
    QRegExp     m_reg;
    QStringList m_intermediateList;
};

QEditValidator::QEditValidator(const QString & reg,QObject* parent):
    QValidator(parent),
    m_reg(reg)
{

}

QValidator::State QEditValidator::validate(QString &input, int &) const
{
    if(!m_reg.exactMatch(input))
    {
        return Intermediate;
    }
    if(m_intermediateList.indexOf(input)>=0)
    {
        return Intermediate;
    }
    return Acceptable;
}

void QEditValidator::setList(QStringList list)
{
    m_intermediateList=list;
}

QValidatorEdit::QValidatorEdit(const QString &reg,QWidget* parent):
    QLineEdit(parent),
    m_validator(new QEditValidator(reg,this))
{
    setValidator(m_validator);
    setContextMenuPolicy(Qt::NoContextMenu);
    connect(this,SIGNAL(textChanged(QString)),this,SLOT(slotTextChanged(QString)));
}

void QValidatorEdit::markIntermediateState()
{
    if(this->hasAcceptableInput())
    {
        setPalette(QPalette());
    }
    else
    {
        QPalette pal=this->palette();
        pal.setColor(QPalette::Active,QPalette::Text,Qt::red);
        setPalette(pal);
    }
}

void QValidatorEdit::setValue(const QString &str)
{
    m_text=str;
    markIntermediateState();
    setText(str);
}

QString QValidatorEdit::value() const
{
    if(hasAcceptableInput())
    {
        return text();
    }
    else
    {
        return m_text;
    }
}

void QValidatorEdit::slotTextChanged(const QString &)
{
    markIntermediateState();
}

void QValidatorEdit::setIntermediateList(QStringList list)
{
    m_validator->setList(list);
}
