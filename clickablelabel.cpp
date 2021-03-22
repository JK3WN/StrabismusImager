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
    if(type==0) emit clicked();
    else if(type==1){
        emit nclicked(this);
    }
    else{
        start=event->pos();
        small=orig.copy().scaled(width(),height(),Qt::KeepAspectRatio);
        painter.begin(&small);
        painter.fillRect(0,0,small.width(),small.height(),QColor(0,0,0,100));
        painter.end();
        setPixmap(small);
    }
}

void ClickableLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(type==2){
        end=event->pos();
        if(end.x()<0) end.setX(0);
        if(end.y()<0) end.setY(0);
        if(end.x()>=width()) end.setX(width()-1);
        if(end.y()>=height()) end.setY(height()-1);
        small=orig.copy().scaled(width(),height(),Qt::KeepAspectRatio);
        painter.begin(&small);
        if(start.x()==end.x()||start.y()==end.y()) painter.fillRect(0,0,small.width(),small.height(),QColor(0,0,0,100));
        else if(start.x()<end.x()){
            if(start.y()<end.y()){
                painter.fillRect(0,0,start.x(),small.height(),QColor(0,0,0,100));
                painter.fillRect(end.x(),0,small.width()-end.x(),small.height(),QColor(0,0,0,100));
                painter.fillRect(start.x(),0,end.x()-start.x(),start.y(),QColor(0,0,0,100));
                painter.fillRect(start.x(),end.y(),end.x()-start.x(),small.height()-end.y(),QColor(0,0,0,100));
            }
            else{
                painter.fillRect(0,0,start.x(),small.height(),QColor(0,0,0,100));
                painter.fillRect(end.x(),0,small.width()-end.x(),small.height(),QColor(0,0,0,100));
                painter.fillRect(start.x(),0,end.x()-start.x(),end.y(),QColor(0,0,0,100));
                painter.fillRect(start.x(),start.y(),end.x()-start.x(),small.height()-start.y(),QColor(0,0,0,100));
            }
        }
        else{
            if(start.y()<end.y()){
                painter.fillRect(0,0,end.x(),small.height(),QColor(0,0,0,100));
                painter.fillRect(start.x(),0,small.width()-start.x(),small.height(),QColor(0,0,0,100));
                painter.fillRect(end.x(),0,start.x()-end.x(),start.y(),QColor(0,0,0,100));
                painter.fillRect(end.x(),end.y(),start.x()-end.x(),small.height()-end.y(),QColor(0,0,0,100));
            }
            else{
                painter.fillRect(0,0,end.x(),small.height(),QColor(0,0,0,100));
                painter.fillRect(start.x(),0,small.width()-start.x(),small.height(),QColor(0,0,0,100));
                painter.fillRect(end.x(),0,start.x()-end.x(),end.y(),QColor(0,0,0,100));
                painter.fillRect(end.x(),start.y(),start.x()-end.x(),small.height()-start.y(),QColor(0,0,0,100));
            }
        }
        painter.end();
        setPixmap(small);
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
        emit dragEnd();
        bigRect=QRect(start,end);
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

void ClickableLabel::filtered(int sx,int sy,int ex,int ey)
{
    small=orig.copy().scaled(width(),height(),Qt::KeepAspectRatio);
    painter.begin(&small);
    painter.fillRect(0,0,sx,small.height(),QColor(0,0,0,100));
    painter.fillRect(ex,0,small.width()-ex,small.height(),QColor(0,0,0,100));
    painter.fillRect(sx,0,ex-sx,sy,QColor(0,0,0,100));
    painter.fillRect(sx,ey,ex-sx,small.height()-ey,QColor(0,0,0,100));
    painter.end();
    setPixmap(small);
}

void ClickableLabel::resetFilter()
{
    setPixmap(orig.copy().scaled(width(),height(),Qt::KeepAspectRatio));
}
