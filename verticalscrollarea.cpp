#include "verticalscrollarea.h"
#include <QDebug>

VerticalScrollArea::VerticalScrollArea(QWidget *parent)
    : QScrollArea(parent)
{
    setWidgetResizable(true);
    content=new QWidget(this);
    setWidget(content);
    grid=new QGridLayout(content);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    grid->setMargin(0);
    grid->setSpacing(0);
    grid->setAlignment(Qt::AlignTop);
}

void VerticalScrollArea::addWidget(QWidget *w, int row, int col)
{
    grid->addWidget(w,row,col);
    adaptSize();
}

int VerticalScrollArea::rowCount()
{
    if(grid->count()==0) return 0;
    return grid->rowCount();
}

void VerticalScrollArea::resetItems()
{
    QLayoutItem *child;
    while((child=grid->takeAt(0))!=nullptr){
        delete child->widget();
    }
}

void VerticalScrollArea::adaptSize()
{
    int h=1.0*height()/nRows;
    content->setFixedHeight(h*rowCount());
    if(grid->columnCount()<3) content->setFixedWidth(viewport()->width()/3*grid->columnCount());
    else content->setFixedWidth(viewport()->width());
}

void VerticalScrollArea::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);
    adaptSize();
}
