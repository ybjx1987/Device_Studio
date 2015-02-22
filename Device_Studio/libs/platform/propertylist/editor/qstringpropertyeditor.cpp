#include "qstringpropertyeditor.h"

#include "qstringeditordialog.h"

#include "../../libs/kernel/property/qstringproperty.h"

QStringPropertyEditor::QStringPropertyEditor(QAbstractProperty * property):
    QButtonPropertyEditor(property)
{

}

void QStringPropertyEditor::buttonClicked()
{

    QStringProperty * pro = (QStringProperty*)m_property;

    QStringEditorDialog dlg(pro,this);
    dlg.exec();
}
