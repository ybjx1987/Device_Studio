#include "styledbar.h"

#include "stylehelper.h"

#include <QStyleOption>
#include <QPainter>

StyledBar::StyledBar(QWidget *parent) : QWidget(parent)
{
    setProperty("panelwidget",true);
    setProperty("panelwidget_singlerow",true);
    setProperty("lightColored",false);
    setFixedHeight(StyleHelper::navigationWidgetHeight());
}

StyledBar::~StyledBar()
{

}

void StyledBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.rect = rect();
    opt.state = QStyle::State_Horizontal;
    style()->drawControl(QStyle::CE_ToolBar,&opt,&painter,this);
    QWidget::paintEvent(e);
}
