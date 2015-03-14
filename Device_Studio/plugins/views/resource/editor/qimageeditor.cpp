#include "qimageeditor.h"

QImageEditor::QImageEditor(QWidget * parent) :
    QAbstractFileEditor(parent)
{

}

QImageEditor::~QImageEditor()
{

}

QStringList QImageEditor::getSupportFile()
{
    QStringList list;
    list<<"png"<<"bmp"<<"jpg";
    return list;
}
