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
    else{
        emit nclicked(this);
    }
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(ro==-1&&co==-1) emit doubleClicked();
    else emit ndoubleClicked(this);
}

QPixmap ClickableLabel::sendPixmap()
{
    return pixmap(Qt::ReturnByValue);
}
