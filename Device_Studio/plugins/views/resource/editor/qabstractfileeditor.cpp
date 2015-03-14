#include "qabstractfileeditor.h"

QAbstractFileEditor::QAbstractFileEditor(QWidget *parent) :
    QWidget(parent)
{

}

QAbstractFileEditor::~QAbstractFileEditor()
{

}

void QAbstractFileEditor::setResourceFile(QResourceFile *resource)
{
    m_resource = resource;
}
