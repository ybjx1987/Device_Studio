#include "qfontpropertyeditor.h"

#include "../../../../libs/kernel/property/qabstractproperty.h"

#include <QFontDialog>

QFontPropertyEditor::QFontPropertyEditor(QAbstractProperty* property):
    QButtonPropertyEditor(property)
{

}

void QFontPropertyEditor::buttonClicked()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok,this);
    QVariant v = QVariant::fromValue<QFont>(f);
    if(ok)
    {
        if(!m_property->equal(v))
        {
            emit valueChanged(v);
        }
    }
}
