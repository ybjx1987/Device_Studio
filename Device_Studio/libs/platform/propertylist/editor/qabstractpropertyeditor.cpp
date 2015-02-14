#include "qabstractpropertyeditor.h"

QAbstractPropertyEditor::QAbstractPropertyEditor(QAbstractProperty* property,
                                                 QWidget* parent) :
    QWidget(parent),
    m_property(property)
{

}

QAbstractPropertyEditor::~QAbstractPropertyEditor()
{

}

