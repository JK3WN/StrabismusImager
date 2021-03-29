#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent,Qt::WindowFlags f)
    : QLabel(parent)
{
    origRect=QRect(-1,-1,0,0);
    setAttribute(Qt::WA_Hover);
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    if(type==0) emit clicked();
    else if(type==1){
        emit nclicked(this,event->pos());
    }
    else{
        if(origRect.topLeft()==QPoint(-1,-1)){
            start=event->pos();
            small=orig.copy().scaled(width(),height(),Qt::KeepAspectRatio);
            painter.begin(&small);
            painter.fillRect(0,0,small.width(),small.height(),QColor(0,0,0,100));
            painter.end();
            setPixmap(small);
        }
        else{
            start=event->pos();
            sizee=bigRect.size();
        }
    }
}

void ClickableLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(type==2){
        if(origRect.topLeft()==QPoint(-1,-1)){
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
        else switch(adjust){
            case 1:{
                end=event->pos();
                bigRect.translate(end-start);
                if(bigRect.top()<0) bigRect.moveTop(0);
                if(bigRect.left()<0) bigRect.moveLeft(0);
                if(bigRect.right()>=width()) bigRect.moveRight(width()-1);
                if(bigRect.bottom()>=height()) bigRect.moveBottom(height()-1);
                small=orig.copy().scaled(width(),height(),Qt::KeepAspectRatio);
                painter.begin(&small);
                painter.fillRect(0,0,bigRect.left(),small.height(),QColor(0,0,0,100));
                painter.fillRect(bigRect.right(),0,small.width()-bigRect.right(),small.height(),QColor(0,0,0,100));
                painter.fillRect(bigRect.left(),0,bigRect.right()-bigRect.left(),bigRect.top(),QColor(0,0,0,100));
                painter.fillRect(bigRect.left(),bigRect.bottom(),bigRect.right()-bigRect.left(),small.height()-bigRect.bottom(),QColor(0,0,0,100));
                painter.setBrush(Qt::white);
                QPen pen(QColor(150,150,150),3);
                painter.setPen(pen);
                painter.drawEllipse(bigRect.topLeft(),6,6);
                painter.drawEllipse(bigRect.topRight(),6,6);
                painter.drawEllipse(bigRect.bottomLeft(),6,6);
                painter.drawEllipse(bigRect.bottomRight(),6,6);
                painter.end();
                setPixmap(small);
                start=end;
                break;
            }
            case 2:{
                end=event->pos();
                bigRect.setTopLeft(end);
                bigRect.setTopLeft(QPoint(bigRect.bottomRight().x()-sizee.scaled(bigRect.size(),Qt::KeepAspectRatio).width(),bigRect.bottomRight().y()-sizee.scaled(bigRect.size(),Qt::KeepAspectRatio).height()));
                if(bigRect.top()<0) bigRect.setTop(0);
                if(bigRect.left()<0) bigRect.setLeft(0);
                bigRect.setTopLeft(QPoint(bigRect.bottomRight().x()-sizee.scaled(bigRect.size(),Qt::KeepAspectRatio).width(),bigRect.bottomRight().y()-sizee.scaled(bigRect.size(),Qt::KeepAspectRatio).height()));
                small=orig.copy().scaled(width(),height(),Qt::KeepAspectRatio);
                painter.begin(&small);
                painter.fillRect(0,0,bigRect.left(),small.height(),QColor(0,0,0,100));
                painter.fillRect(bigRect.right(),0,small.width()-bigRect.right(),small.height(),QColor(0,0,0,100));
                painter.fillRect(bigRect.left(),0,bigRect.right()-bigRect.left(),bigRect.top(),QColor(0,0,0,100));
                painter.fillRect(bigRect.left(),bigRect.bottom(),bigRect.right()-bigRect.left(),small.height()-bigRect.bottom(),QColor(0,0,0,100));
                painter.setBrush(Qt::white);
                QPen pen(QColor(150,150,150),3);
                painter.setPen(pen);
                painter.drawEllipse(bigRect.topLeft(),6,6);
                painter.drawEllipse(bigRect.topRight(),6,6);
                painter.drawEllipse(bigRect.bottomLeft(),6,6);
                painter.drawEllipse(bigRect.bottomRight(),6,6);
                painter.end();
                setPixmap(small);
                break;
            }
            case 3:{
                break;
            }
            case 4:{
                break;
            }
            case 5:{
                break;
            }
            default:
                break;
        }
    }
    else if(type==1){
        emit ndragged(this,event->pos());
    }
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(type==2){
        if(origRect.topLeft()==QPoint(-1,-1)){
            end=event->pos();
            if(end.x()<0) end.setX(0);
            if(end.y()<0) end.setY(0);
            if(end.x()>=width()) end.setX(width()-1);
            if(end.y()>=height()) end.setY(height()-1);
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
            smallRect=QRect(start/3,end/3);
            origRect=QRect(start.x()*orig.width()/width(),start.y()*orig.height()/height(),(end.x()-start.x())*orig.width()/width(),(end.y()-start.y())*orig.height()/height());
            small=this->pixmap(Qt::ReturnByValue).copy().scaled(width(),height(),Qt::KeepAspectRatio);
            painter.begin(&small);
            painter.setBrush(Qt::white);
            QPen pen(QColor(150,150,150),3);
            painter.setPen(pen);
            painter.drawEllipse(bigRect.topLeft(),6,6);
            painter.drawEllipse(bigRect.topRight(),6,6);
            painter.drawEllipse(bigRect.bottomLeft(),6,6);
            painter.drawEllipse(bigRect.bottomRight(),6,6);
            painter.end();
            setPixmap(small);
        }
        else{
            origRect.moveTopLeft(QPoint(bigRect.left()*orig.width()/width(),bigRect.top()*orig.height()/height()));
            smallRect.moveTopLeft(QPoint(bigRect.left()/3,bigRect.top()/3));
            origRect.setSize(bigRect.size()*orig.width()/width());
            smallRect.setSize(bigRect.size()/3);
            emit dragEnd();
        }
    }
    else if(type==1){
        emit ndragEnd(this,event->pos());
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

void ClickableLabel::filtered(int sx,int sy,int ex,int ey,int bw,int bh)
{
    origRect=QRect(sx,sy,(ex-sx),(ey-sy));
    bigRect=QRect(sx*bw/orig.width(),sy*bh/orig.height(),(ex-sx)*bw/orig.width(),(ey-sy)*bh/orig.height());
    smallRect=QRect(bigRect.topLeft()/3,bigRect.bottomRight()/3);
    small=orig.copy().scaled(width(),height(),Qt::KeepAspectRatio);
    painter.begin(&small);
    painter.fillRect(0,0,smallRect.left(),small.height(),QColor(0,0,0,100));
    painter.fillRect(smallRect.right(),0,small.width()-smallRect.right(),small.height(),QColor(0,0,0,100));
    painter.fillRect(smallRect.left(),0,smallRect.right()-smallRect.left(),smallRect.top(),QColor(0,0,0,100));
    painter.fillRect(smallRect.left(),smallRect.bottom(),smallRect.right()-smallRect.left(),small.height()-smallRect.bottom(),QColor(0,0,0,100));
    painter.end();
    setPixmap(small);
}

void ClickableLabel::resetFilter()
{
    if(!orig.isNull()) setPixmap(orig.copy().scaled(width(),height(),Qt::KeepAspectRatio));
    origRect.setTopLeft(QPoint(-1,-1));
}

bool ClickableLabel::event(QEvent *e)
{
    if(e->type()==QMouseEvent::MouseButtonPress) down=true;
    if(e->type()==QMouseEvent::MouseButtonRelease) down=false;
    if(e->type()==QHoverEvent::HoverMove&&!down){
        hoverMove(static_cast<QHoverEvent*>(e));
        return true;
    }
    return QWidget::event(e);
}

void ClickableLabel::hoverMove(QHoverEvent *event)
{
    if(this->type==2){
        if(origRect.topLeft()==QPoint(-1,-1)){
            setCursor(Qt::CrossCursor);
            adjust=0;
        }
        else if((bigRect.topLeft()-event->pos()).manhattanLength()<=6){
            setCursor(Qt::SizeFDiagCursor);
            adjust=2;
        }
        else if((bigRect.topRight()-event->pos()).manhattanLength()<=6){
            setCursor(Qt::SizeBDiagCursor);
            adjust=3;
        }
        else if((bigRect.bottomLeft()-event->pos()).manhattanLength()<=6){
            setCursor(Qt::SizeBDiagCursor);
            adjust=4;
        }
        else if((bigRect.bottomRight()-event->pos()).manhattanLength()<=6){
            setCursor(Qt::SizeFDiagCursor);
            adjust=5;
        }
        else if(bigRect.contains(event->pos())){
            setCursor(Qt::SizeAllCursor);
            adjust=1;
        }
        else{
            setCursor(Qt::ArrowCursor);
            adjust=-1;
        }
    }
}
