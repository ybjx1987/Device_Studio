#include "qimageeditor.h"

#include "qimageview.h"

#include "../../../../libs/kernel/resource/qresourcefile.h"

#include <QVBoxLayout>

QImageEditor::QImageEditor(QWidget * parent) :
    QAbstractFileEditor(parent),
    m_imageView(new QImageView)
{
    QVBoxLayout * vb = new QVBoxLayout;
    vb->setMargin(0);
    vb->setSpacing(0);

    vb->addWidget(m_imageView);

    setLayout(vb);
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

void QImageEditor::setResourceFile(QResourceFile *resource)
{
    m_imageView->setImage(resource->getData());
    m_resource = resource;
}
