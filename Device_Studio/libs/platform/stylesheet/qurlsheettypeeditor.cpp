#include "qurlsheettypeeditor.h"

#include "qimageeditor.h"

#include "../../kernel/stylesheet/type/qabstractsheettype.h"

#include <QHBoxLayout>
#include <QVariant>

QUrlSheetTypeEditor::QUrlSheetTypeEditor(QAbstractSheetType * property,QWidget * parent):
    QAbstractSheetPropertyEditor(property,parent),
    m_imageEditor(new QImageEditor(property))
{
    setProperty("no-ManhattanStyle",true);
    QHBoxLayout * hb = new QHBoxLayout;
    hb->setMargin(0);
    hb->setSpacing(0);
    hb->addWidget(m_imageEditor);
    setLayout(hb);

    connect(m_imageEditor,SIGNAL(valueChanged(QString)),
            this,SLOT(valueChanged(QString)));
}

QUrlSheetTypeEditor::~QUrlSheetTypeEditor()
{

}

void QUrlSheetTypeEditor::propertyChanged()
{

}

void QUrlSheetTypeEditor::valueChanged(const QString &value)
{
    m_property->setValue(value);
}
