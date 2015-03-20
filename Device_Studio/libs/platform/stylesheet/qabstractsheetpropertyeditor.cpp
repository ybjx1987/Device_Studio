#include "qabstractsheetpropertyeditor.h"

#include "../../kernel/stylesheet/type/qabstractsheettype.h"

#include <QPainter>

QAbstractSheetPropertyEditor::QAbstractSheetPropertyEditor(QAbstractSheetType * property,
                                                           QWidget *parent) :
    QWidget(parent),
    m_property(property)
{
    setFocusPolicy(Qt::StrongFocus);
    connect(m_property,SIGNAL(valueChanged(QVariant)),
            this,SLOT(propertyChanged()));

}

QAbstractSheetPropertyEditor::~QAbstractSheetPropertyEditor()
{

}

void QAbstractSheetPropertyEditor::propertyChanged()
{

}

void QAbstractSheetPropertyEditor::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.fillRect(rect(),QColor(255,255,255));
}
