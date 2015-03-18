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

QList<QAction*> QImageEditor::getToolBarActions()
{
    QList<QAction*> list;

    QAction * ac;

    ac = new QAction(QIcon(":/inner/images/background.png"),tr("Background"),this);
    list.append(ac);
    connect(ac,SIGNAL(triggered()),m_imageView,SLOT(changedBackground()));
    ac->setCheckable(true);

    ac = new QAction(QIcon(":/inner/images/outline.png"),tr("Outline"),this);
    list.append(ac);
    connect(ac,SIGNAL(triggered()),m_imageView,SLOT(changedOutline()));
    ac->setCheckable(true);
    ac->setChecked(true);

    ac = new QAction(QIcon(":/inner/images/fitinscreen.png"),tr("Fit Screen"),this);
    list.append(ac);
    connect(ac,SIGNAL(triggered()),m_imageView,SLOT(fitToScreen()));

    ac = new QAction(QIcon(":/inner/images/originalsize.png"),tr("Original Size"),this);
    list.append(ac);
    connect(ac,SIGNAL(triggered()),m_imageView,SLOT(resetToOriginalSize()));

    ac = new QAction(QIcon(":/inner/images/zoomin.png"),tr("Zoomin"),this);
    list.append(ac);
    connect(ac,SIGNAL(triggered()),m_imageView,SLOT(zoomIn()));

    ac = new QAction(QIcon(":/inner/images/zoomout.png"),tr("Zoomout"),this);
    list.append(ac);
    connect(ac,SIGNAL(triggered()),m_imageView,SLOT(zoomOut()));

    ac = new QAction(this);
    ac->setSeparator(true);
    list.append(ac);

    return list;
}
