#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent,Qt::WindowFlags f)
    : QLabel(parent)
{
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    if(ro==-1&&co==-1) emit clicked();
    else emit nclicked(ro,co);
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(ro==-1&&co==-1) emit doubleClicked();
    else emit ndoubleClicked(ro,co);
}
