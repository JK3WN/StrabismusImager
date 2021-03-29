#include "imager.h"
#include "ui_imager.h"

Imager::Imager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Imager)
{
    ui->setupUi(this);
    resetImg();
    ui->saveBtn->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->backBtn->setIcon(style()->standardIcon(QStyle::SP_FileDialogBack));
    ui->resetBtn->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    ui->resetBtn->setEnabled(0);
    ui->saveBtn->setEnabled(0);
    ui->dragLabel->setVisible(0);
    ui->bigLabel->type=2;

    connect(ui->actionSelect_Folder,SIGNAL(triggered()),this,SLOT(chkFolder()));
    connect(ui->backBtn,SIGNAL(clicked()),this,SLOT(closeBig()));
    connect(ui->saveBtn,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->resetBtn,SIGNAL(clicked()),this,SLOT(resetImg()));
    connect(ui->bigLabel,SIGNAL(dragEnd()),this,SLOT(setCoords()));
    connect(this,SIGNAL(resetAll()),ui->bigLabel,SLOT(resetFilter()));
}

Imager::~Imager()
{
    delete ui;
}

void Imager::chkFolder()
{
    dir=new QDir(QFileDialog::getExistingDirectory(this,"Select Folder",QDir::homePath()+"/Desktop"));
    list=dir->entryList(QStringList()<<"*.png"<<"*.jpg"<<"*.bmp",QDir::Files);
    mrow=0;
    mcol=0;
    ui->imgArea->resetItems();
    resetImg();
    for(const QString& v:list){
        ClickableLabel *label=new ClickableLabel();
        QPixmap pix(dir->absoluteFilePath(v));
        label->setFixedSize(ui->imgArea->viewport()->width()/3,ui->imgArea->height()/3);
        QPixmap temp(label->size());
        temp=temp.scaled(pix.size(),Qt::KeepAspectRatioByExpanding);
        painter.begin(&temp);
        painter.fillRect(0,0,temp.width(),temp.height(),QColor(255,255,255));
        painter.drawPixmap((temp.width()-pix.width())/2,(temp.height()-pix.height())/2,pix.width(),pix.height(),pix);
        painter.end();
        pix=temp;
        label->setPixmap(pix.scaled(label->size(),Qt::KeepAspectRatio));
        label->setAlignment(Qt::AlignCenter);
        label->orig=pix;
        resSize=pix.size();
        ui->imgArea->addWidget(label,mrow,mcol);
        label->ro=mrow;
        label->co=mcol;
        label->type=1;
        label->setLineWidth(3);
        connect(label,SIGNAL(ndoubleClicked(ClickableLabel*)),this,SLOT(sendBig(ClickableLabel*)));
        connect(label,SIGNAL(nclicked(ClickableLabel*,QPoint)),this,SLOT(selection(ClickableLabel*,QPoint)));
        connect(label,SIGNAL(ndragged(ClickableLabel*,QPoint)),this,SLOT(dragging(ClickableLabel*,QPoint)));
        connect(label,SIGNAL(ndragEnd(ClickableLabel*,QPoint)),this,SLOT(dragComp(ClickableLabel*,QPoint)));
        connect(this,SIGNAL(filterAll(int,int,int,int,int,int)),label,SLOT(filtered(int,int,int,int,int,int)));
        connect(this,SIGNAL(resetAll()),label,SLOT(resetFilter()));
        prev=label;
        mcol++;
        if(mcol>=3){
            mcol=mcol-3;
            mrow++;
        }
    }
}

void Imager::sendBig(ClickableLabel *label)
{
    if(!coord) ui->bigLabel->setPixmap(label->orig.scaled(ui->bigLabel->size(),Qt::KeepAspectRatio));
    else{
        QPixmap temp=label->orig.copy().scaled(ui->bigLabel->size(),Qt::KeepAspectRatio);
        painter.begin(&temp);
        painter.fillRect(0,0,label->bigRect.left(),temp.height(),QColor(0,0,0,100));
        painter.fillRect(label->bigRect.right(),0,temp.width()-label->bigRect.right(),temp.height(),QColor(0,0,0,100));
        painter.fillRect(label->bigRect.left(),0,label->bigRect.right()-label->bigRect.left(),label->bigRect.top(),QColor(0,0,0,100));
        painter.fillRect(label->bigRect.left(),label->bigRect.bottom(),label->bigRect.right()-label->bigRect.left(),temp.height()-label->bigRect.bottom(),QColor(0,0,0,100));
        painter.setBrush(Qt::white);
        QPen pen(QColor(150,150,150),3);
        painter.setPen(pen);
        painter.drawEllipse(label->bigRect.topLeft(),6,6);
        painter.drawEllipse(label->bigRect.topRight(),6,6);
        painter.drawEllipse(label->bigRect.bottomLeft(),6,6);
        painter.drawEllipse(label->bigRect.bottomRight(),6,6);
        painter.end();
        ui->bigLabel->setPixmap(temp);
        ui->bigLabel->bigRect=QRect(label->bigRect);
    }
    ui->bigLabel->orig=label->orig.copy();
    ui->imgArea->setVisible(0);
    count++;
}

void Imager::resetImg()
{
    memset(capt,false,sizeof(capt));
    coord=false;
    ui->resetBtn->setEnabled(0);
    ui->saveBtn->setEnabled(0);
    defimg.load(":/image/arrow1.PNG");
    ui->resLabel1->setPixmap(defimg.scaled(ui->resLabel1->size(),Qt::KeepAspectRatio));
    defimg.load(":/image/arrow2.PNG");
    ui->resLabel2->setPixmap(defimg.scaled(ui->resLabel2->size(),Qt::KeepAspectRatio));
    defimg.load(":/image/arrow3.PNG");
    ui->resLabel3->setPixmap(defimg.scaled(ui->resLabel3->size(),Qt::KeepAspectRatio));
    defimg.load(":/image/arrow4.PNG");
    ui->resLabel4->setPixmap(defimg.scaled(ui->resLabel4->size(),Qt::KeepAspectRatio));
    defimg.load(":/image/arrow5.PNG");
    ui->resLabel5->setPixmap(defimg.scaled(ui->resLabel5->size(),Qt::KeepAspectRatio));
    defimg.load(":/image/arrow6.PNG");
    ui->resLabel6->setPixmap(defimg.scaled(ui->resLabel6->size(),Qt::KeepAspectRatio));
    defimg.load(":/image/arrow7.PNG");
    ui->resLabel7->setPixmap(defimg.scaled(ui->resLabel7->size(),Qt::KeepAspectRatio));
    defimg.load(":/image/arrow8.PNG");
    ui->resLabel8->setPixmap(defimg.scaled(ui->resLabel8->size(),Qt::KeepAspectRatio));
    defimg.load(":/image/arrow9.PNG");
    ui->resLabel9->setPixmap(defimg.scaled(ui->resLabel9->size(),Qt::KeepAspectRatio));
    emit resetAll();
    if(!ui->imgArea->isVisible()) count=1;
    else count=0;
}

void Imager::closeBig()
{
    ui->imgArea->setVisible(1);
    count++;
}

void Imager::selection(ClickableLabel *label,QPoint point)
{
    selimg=label->orig.copy();
    selRect=QRect(label->origRect.x(),label->origRect.y(),label->origRect.width(),label->origRect.height());
    prev=label;
    ui->dragLabel->setVisible(1);
    start=point;
    ui->dragLabel->raise();
    ui->dragLabel->setFixedSize(label->size());
    ui->dragLabel->move(label->pos().x(),label->pos().y()-ui->imgArea->verticalScrollBar()->value());
    ui->dragLabel->setPixmap(label->pixmap(Qt::ReturnByValue));
}

void Imager::res1Clicked()
{
    if(selimg.isNull()) return;
    capt[0]=true;
    if(!coord) resimg[0]=selimg.copy();
    else resimg[0]=selimg.copy(selRect);
    ui->resLabel1->setPixmap(resimg[0].scaled(ui->resLabel1->size(),Qt::KeepAspectRatio));
}

void Imager::res2Clicked()
{
    if(selimg.isNull()) return;
    capt[1]=true;
    if(!coord) resimg[1]=selimg.copy();
    else resimg[1]=selimg.copy(selRect);
    ui->resLabel2->setPixmap(resimg[1].scaled(ui->resLabel2->size(),Qt::KeepAspectRatio));
}

void Imager::res3Clicked()
{
    if(selimg.isNull()) return;
    capt[2]=true;
    if(!coord) resimg[2]=selimg.copy();
    else resimg[2]=selimg.copy(selRect);
    ui->resLabel3->setPixmap(resimg[2].scaled(ui->resLabel3->size(),Qt::KeepAspectRatio));
}

void Imager::res4Clicked()
{
    if(selimg.isNull()) return;
    capt[3]=true;
    if(!coord) resimg[3]=selimg.copy();
    else resimg[3]=selimg.copy(selRect);
    ui->resLabel4->setPixmap(resimg[3].scaled(ui->resLabel4->size(),Qt::KeepAspectRatio));
}

void Imager::res5Clicked()
{
    if(selimg.isNull()) return;
    capt[4]=true;
    if(!coord) resimg[4]=selimg.copy();
    else resimg[4]=selimg.copy(selRect);
    ui->resLabel5->setPixmap(resimg[4].scaled(ui->resLabel5->size(),Qt::KeepAspectRatio));
}

void Imager::res6Clicked()
{
    if(selimg.isNull()) return;
    capt[5]=true;
    if(!coord) resimg[5]=selimg.copy();
    else resimg[5]=selimg.copy(selRect);
    ui->resLabel6->setPixmap(resimg[5].scaled(ui->resLabel6->size(),Qt::KeepAspectRatio));
}

void Imager::res7Clicked()
{
    if(selimg.isNull()) return;
    capt[6]=true;
    if(!coord) resimg[6]=selimg.copy();
    else resimg[6]=selimg.copy(selRect);
    ui->resLabel7->setPixmap(resimg[6].scaled(ui->resLabel7->size(),Qt::KeepAspectRatio));
}

void Imager::res8Clicked()
{
    if(selimg.isNull()) return;
    capt[7]=true;
    if(!coord) resimg[7]=selimg.copy();
    else resimg[7]=selimg.copy(selRect);
    ui->resLabel8->setPixmap(resimg[7].scaled(ui->resLabel8->size(),Qt::KeepAspectRatio));
}

void Imager::res9Clicked()
{
    if(selimg.isNull()) return;
    capt[8]=true;
    if(!coord) resimg[8]=selimg.copy();
    else resimg[8]=selimg.copy(selRect);
    ui->resLabel9->setPixmap(resimg[8].scaled(ui->resLabel9->size(),Qt::KeepAspectRatio));
}

void Imager::save()
{
    max=0;
    for(int i=0;i<9;i++){
        if(capt[i]) max++;
    }
    if(max==1) return;
    QDir::setCurrent(dir->absolutePath());
    QPixmap print(resSize.width()*3,resSize.height()*3);
    painter.begin(&print);
    painter.fillRect(0,0,resSize.width()*3,resSize.height()*3,QColor(255,255,255));
    if(capt[0]) painter.drawPixmap(0,0,resSize.width(),resSize.height(),resimg[0],0,0,resimg[0].width(),resimg[0].height());
    if(capt[1]) painter.drawPixmap(resSize.width(),0,resSize.width(),resSize.height(),resimg[1],0,0,resimg[1].width(),resimg[1].height());
    if(capt[2]) painter.drawPixmap(resSize.width()*2,0,resSize.width(),resSize.height(),resimg[2],0,0,resimg[2].width(),resimg[2].height());
    if(capt[3]) painter.drawPixmap(0,resSize.height(),resSize.width(),resSize.height(),resimg[3],0,0,resimg[3].width(),resimg[3].height());
    if(capt[4]) painter.drawPixmap(resSize.width(),resSize.height(),resSize.width(),resSize.height(),resimg[4],0,0,resimg[4].width(),resimg[4].height());
    if(capt[5]) painter.drawPixmap(resSize.width()*2,resSize.height(),resSize.width(),resSize.height(),resimg[5],0,0,resimg[5].width(),resimg[5].height());
    if(capt[6]) painter.drawPixmap(0,resSize.height()*2,resSize.width(),resSize.height(),resimg[6],0,0,resimg[6].width(),resimg[6].height());
    if(capt[7]) painter.drawPixmap(resSize.width(),resSize.height()*2,resSize.width(),resSize.height(),resimg[7],0,0,resimg[7].width(),resimg[7].height());
    if(capt[8]) painter.drawPixmap(resSize.width()*2,resSize.height()*2,resSize.width(),resSize.height(),resimg[8],0,0,resimg[8].width(),resimg[8].height());
    painter.end();
    imgFile.setFileName("NineCardinal.png");
    imgFile.open(QIODevice::WriteOnly);
    print.save(&imgFile,"PNG");
    imgFile.close();
}

void Imager::setCoords()
{
    if(!coord){
        memset(capt,false,sizeof(capt));
        defimg.load(":/image/arrow1.PNG");
        ui->resLabel1->setPixmap(defimg.scaled(ui->resLabel1->size(),Qt::KeepAspectRatio));
        defimg.load(":/image/arrow2.PNG");
        ui->resLabel2->setPixmap(defimg.scaled(ui->resLabel2->size(),Qt::KeepAspectRatio));
        defimg.load(":/image/arrow3.PNG");
        ui->resLabel3->setPixmap(defimg.scaled(ui->resLabel3->size(),Qt::KeepAspectRatio));
        defimg.load(":/image/arrow4.PNG");
        ui->resLabel4->setPixmap(defimg.scaled(ui->resLabel4->size(),Qt::KeepAspectRatio));
        defimg.load(":/image/arrow5.PNG");
        ui->resLabel5->setPixmap(defimg.scaled(ui->resLabel5->size(),Qt::KeepAspectRatio));
        defimg.load(":/image/arrow6.PNG");
        ui->resLabel6->setPixmap(defimg.scaled(ui->resLabel6->size(),Qt::KeepAspectRatio));
        defimg.load(":/image/arrow7.PNG");
        ui->resLabel7->setPixmap(defimg.scaled(ui->resLabel7->size(),Qt::KeepAspectRatio));
        defimg.load(":/image/arrow8.PNG");
        ui->resLabel8->setPixmap(defimg.scaled(ui->resLabel8->size(),Qt::KeepAspectRatio));
        defimg.load(":/image/arrow9.PNG");
        ui->resLabel9->setPixmap(defimg.scaled(ui->resLabel9->size(),Qt::KeepAspectRatio));
        stx=ui->bigLabel->start.x()*ui->bigLabel->orig.width()/ui->bigLabel->pixmap(Qt::ReturnByValue).width();
        sty=ui->bigLabel->start.y()*ui->bigLabel->orig.height()/ui->bigLabel->pixmap(Qt::ReturnByValue).height();
        enx=ui->bigLabel->end.x()*ui->bigLabel->orig.width()/ui->bigLabel->pixmap(Qt::ReturnByValue).width();
        eny=ui->bigLabel->end.y()*ui->bigLabel->orig.height()/ui->bigLabel->pixmap(Qt::ReturnByValue).height();
        selRect=QRect(stx,sty,enx-stx,eny-sty);
        resSize=QSize(enx-stx,eny-sty);
        emit filterAll(stx,sty,enx,eny,ui->bigLabel->pixmap(Qt::ReturnByValue).width(),ui->bigLabel->pixmap(Qt::ReturnByValue).height());
        coord=true;
        ui->resetBtn->setEnabled(1);
        ui->saveBtn->setEnabled(1);
    }
    else{
        prev->origRect=QRect(ui->bigLabel->origRect);
        prev->bigRect=QRect(ui->bigLabel->bigRect);
        prev->smallRect=QRect(ui->bigLabel->smallRect);
        QPixmap temp=prev->orig.copy().scaled(prev->size(),Qt::KeepAspectRatio);
        painter.begin(&temp);
        painter.fillRect(0,0,prev->smallRect.left(),temp.height(),QColor(0,0,0,100));
        painter.fillRect(prev->smallRect.right(),0,temp.width()-prev->smallRect.right(),temp.height(),QColor(0,0,0,100));
        painter.fillRect(prev->smallRect.left(),0,prev->smallRect.right()-prev->smallRect.left(),prev->smallRect.top(),QColor(0,0,0,100));
        painter.fillRect(prev->smallRect.left(),prev->smallRect.bottom(),prev->smallRect.right()-prev->smallRect.left(),temp.height()-prev->smallRect.bottom(),QColor(0,0,0,100));
        painter.end();
        prev->setPixmap(temp);
        selRect=QRect(prev->origRect);
    }
}

void Imager::dragging(ClickableLabel *label,QPoint point)
{
    end=point;
    ui->dragLabel->move((label->pos()+end-start).x(),(label->pos()+end-start).y()-ui->imgArea->verticalScrollBar()->value());
}

void Imager::dragComp(ClickableLabel *label,QPoint point)
{
    ui->dragLabel->setVisible(0);
    if(QRect(ui->resLabel1->pos(),ui->resLabel1->size()).contains((label->pos()+point).x(),(label->pos()+point).y()-ui->imgArea->verticalScrollBar()->value())) res1Clicked();
    if(QRect(ui->resLabel2->pos(),ui->resLabel2->size()).contains((label->pos()+point).x(),(label->pos()+point).y()-ui->imgArea->verticalScrollBar()->value())) res2Clicked();
    if(QRect(ui->resLabel3->pos(),ui->resLabel3->size()).contains((label->pos()+point).x(),(label->pos()+point).y()-ui->imgArea->verticalScrollBar()->value())) res3Clicked();
    if(QRect(ui->resLabel4->pos(),ui->resLabel4->size()).contains((label->pos()+point).x(),(label->pos()+point).y()-ui->imgArea->verticalScrollBar()->value())) res4Clicked();
    if(QRect(ui->resLabel5->pos(),ui->resLabel5->size()).contains((label->pos()+point).x(),(label->pos()+point).y()-ui->imgArea->verticalScrollBar()->value())) res5Clicked();
    if(QRect(ui->resLabel6->pos(),ui->resLabel6->size()).contains((label->pos()+point).x(),(label->pos()+point).y()-ui->imgArea->verticalScrollBar()->value())) res6Clicked();
    if(QRect(ui->resLabel7->pos(),ui->resLabel7->size()).contains((label->pos()+point).x(),(label->pos()+point).y()-ui->imgArea->verticalScrollBar()->value())) res7Clicked();
    if(QRect(ui->resLabel8->pos(),ui->resLabel8->size()).contains((label->pos()+point).x(),(label->pos()+point).y()-ui->imgArea->verticalScrollBar()->value())) res8Clicked();
    if(QRect(ui->resLabel9->pos(),ui->resLabel9->size()).contains((label->pos()+point).x(),(label->pos()+point).y()-ui->imgArea->verticalScrollBar()->value())) res9Clicked();
}

void Imager::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape){
        if(count==1) resetImg();
        else if(!ui->imgArea->isVisible()){
            prev->filtered(stx,sty,enx,eny,ui->bigLabel->pixmap(Qt::ReturnByValue).width(),ui->bigLabel->pixmap(Qt::ReturnByValue).height());
            ui->bigLabel->origRect=QRect(prev->origRect);
            ui->bigLabel->bigRect=QRect(prev->bigRect);
            ui->bigLabel->smallRect=QRect(prev->smallRect);
            QPixmap temp=prev->orig.copy().scaled(ui->bigLabel->size(),Qt::KeepAspectRatio);
            painter.begin(&temp);
            painter.fillRect(0,0,prev->bigRect.left(),temp.height(),QColor(0,0,0,100));
            painter.fillRect(prev->bigRect.right(),0,temp.width()-prev->bigRect.right(),temp.height(),QColor(0,0,0,100));
            painter.fillRect(prev->bigRect.left(),0,prev->bigRect.right()-prev->bigRect.left(),prev->bigRect.top(),QColor(0,0,0,100));
            painter.fillRect(prev->bigRect.left(),prev->bigRect.bottom(),prev->bigRect.right()-prev->bigRect.left(),temp.height()-prev->bigRect.bottom(),QColor(0,0,0,100));
            painter.end();
            ui->bigLabel->setPixmap(temp);
            selRect=QRect(prev->origRect);
        }
    }
    setFocus();
}
