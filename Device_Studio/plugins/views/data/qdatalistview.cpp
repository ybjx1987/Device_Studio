#include "qdatalistview.h"

QDataListView::QDataListView(QWidget* parent):
    QBaseListView(parent)
{
    setHeaderLabels(QStringList()<<tr("Name")<<tr("Value")<<tr("NeedSave")
                    <<tr("Explanation"));
}
