#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent,Qt::WindowFlags f)
    : QLabel(parent)
{
    rubberBand=new QRubberBand(QRubberBand::Rectangle,this);
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    if(type==0) emit clicked();
    else if(type==1) emit nclicked(this);
    else{
        start=event->pos();
        if(!rubberBand) rubberBand=new QRubberBand(QRubberBand::Rectangle,this);
        rubberBand->setGeometry(QRect(start,QSize()));
        rubberBand->show();
    }
}

void ClickableLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(type==2){
        end=event->pos();
        if(end.x()<0) end.setX(0);
        if(end.y()<0) end.setY(0);
        if(end.x()>=this->width()) end.setX(this->width()-1);
        if(end.y()>=this->height()) end.setY(this->height()-1);
        rubberBand->setGeometry(QRect(start,end).normalized());
    }
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(type==2){
        end=event->pos();
        if(end.x()<0) end.setX(0);
        if(end.y()<0) end.setY(0);
        if(end.x()>=this->width()) end.setX(this->width()-1);
        if(end.y()>=this->height()) end.setY(this->height()-1);
        rubberBand->setGeometry(QRect(start,end).normalized());
        if(start.x()>end.x()){
            int temp=start.x();
            start.setX(end.x());
            end.setX(temp);
        }
        if(start.y()>end.y()){
            int temp=start.y();
            start.setY(end.y());
            end.setY(temp);
        }
        emit sendCoords(start.x()*orig.width()/pixmap(Qt::ReturnByValue).width(),start.y()*orig.height()/pixmap(Qt::ReturnByValue).height(),end.x()*orig.width()/pixmap(Qt::ReturnByValue).width(),end.y()*orig.height()/pixmap(Qt::ReturnByValue).height());
    }
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(type!=1) emit doubleClicked();
    else emit ndoubleClicked(this);
}

QPixmap ClickableLabel::sendPixmap()
{
    return pixmap(Qt::ReturnByValue);
}
