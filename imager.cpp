#include "imager.h"
#include "ui_imager.h"

Imager::Imager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Imager)
{
    ui->setupUi(this);
    resetImg();
    ui->saveBtn->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));

    connect(ui->actionSelect_Folder,SIGNAL(triggered()),this,SLOT(chkFolder()));
    connect(ui->bigLabel,SIGNAL(doubleClicked()),this,SLOT(closeBig()));
    connect(ui->saveBtn,SIGNAL(clicked()),this,SLOT(save()));

    connect(ui->resLabel1,SIGNAL(clicked()),this,SLOT(res1Clicked()));
    connect(ui->resLabel2,SIGNAL(clicked()),this,SLOT(res2Clicked()));
    connect(ui->resLabel3,SIGNAL(clicked()),this,SLOT(res3Clicked()));
    connect(ui->resLabel4,SIGNAL(clicked()),this,SLOT(res4Clicked()));
    connect(ui->resLabel5,SIGNAL(clicked()),this,SLOT(res5Clicked()));
    connect(ui->resLabel6,SIGNAL(clicked()),this,SLOT(res6Clicked()));
    connect(ui->resLabel7,SIGNAL(clicked()),this,SLOT(res7Clicked()));
    connect(ui->resLabel8,SIGNAL(clicked()),this,SLOT(res8Clicked()));
    connect(ui->resLabel9,SIGNAL(clicked()),this,SLOT(res9Clicked()));
}

Imager::~Imager()
{
    delete ui;
}

void Imager::chkFolder()
{
    dir=new QDir(QFileDialog::getExistingDirectory(this,"Select Folder"));
    list=dir->entryList(QStringList()<<"*.png"<<"*.jpg",QDir::Files);
    mrow=0;
    mcol=0;
    ui->imgArea->resetItems();
    for(const QString& v:list){
        ClickableLabel *label=new ClickableLabel();
        QPixmap pix(dir->absoluteFilePath(v));
        label->setFixedSize(ui->imgArea->viewport()->width()/3,ui->imgArea->height()/3);
        label->setPixmap(pix.scaled(label->size(),Qt::KeepAspectRatio));
        label->setAlignment(Qt::AlignCenter);
        label->orig=pix;
        ui->imgArea->addWidget(label,mrow,mcol);
        label->ro=mrow;
        label->co=mcol;
        label->setLineWidth(3);
        connect(label,SIGNAL(ndoubleClicked(ClickableLabel*)),this,SLOT(sendBig(ClickableLabel*)));
        connect(label,SIGNAL(nclicked(ClickableLabel*)),this,SLOT(selection(ClickableLabel*)));
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
    ui->bigLabel->setPixmap(label->orig.scaled(ui->bigLabel->size(),Qt::KeepAspectRatio));
    ui->imgArea->setVisible(0);
}

void Imager::resetImg()
{
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
}

void Imager::closeBig()
{
    ui->imgArea->setVisible(1);
}

void Imager::selection(ClickableLabel *label)
{
    selimg=label->orig.copy();
    prev->setFrameStyle(QFrame::NoFrame);
    label->setFrameStyle(QFrame::Panel|QFrame::Raised);
    prev=label;
}

void Imager::res1Clicked()
{
    if(selimg.isNull()) return;
    capt[0]=true;
    resimg[0]=selimg.copy();
    resSize=selimg.size();
    ui->resLabel1->setPixmap(selimg.scaled(ui->resLabel1->size(),Qt::KeepAspectRatio));
}

void Imager::res2Clicked()
{
    if(selimg.isNull()) return;
    capt[1]=true;
    resimg[1]=selimg.copy();
    resSize=selimg.size();
    ui->resLabel2->setPixmap(selimg.scaled(ui->resLabel2->size(),Qt::KeepAspectRatio));
}

void Imager::res3Clicked()
{
    if(selimg.isNull()) return;
    capt[2]=true;
    resimg[2]=selimg.copy();
    resSize=selimg.size();
    ui->resLabel3->setPixmap(selimg.scaled(ui->resLabel3->size(),Qt::KeepAspectRatio));
}

void Imager::res4Clicked()
{
    if(selimg.isNull()) return;
    capt[3]=true;
    resimg[3]=selimg.copy();
    resSize=selimg.size();
    ui->resLabel4->setPixmap(selimg.scaled(ui->resLabel4->size(),Qt::KeepAspectRatio));
}

void Imager::res5Clicked()
{
    if(selimg.isNull()) return;
    capt[4]=true;
    resimg[4]=selimg.copy();
    resSize=selimg.size();
    ui->resLabel5->setPixmap(selimg.scaled(ui->resLabel5->size(),Qt::KeepAspectRatio));
}

void Imager::res6Clicked()
{
    if(selimg.isNull()) return;
    capt[5]=true;
    resimg[5]=selimg.copy();
    resSize=selimg.size();
    ui->resLabel6->setPixmap(selimg.scaled(ui->resLabel6->size(),Qt::KeepAspectRatio));
}

void Imager::res7Clicked()
{
    if(selimg.isNull()) return;
    capt[6]=true;
    resimg[6]=selimg.copy();
    resSize=selimg.size();
    ui->resLabel7->setPixmap(selimg.scaled(ui->resLabel7->size(),Qt::KeepAspectRatio));
}

void Imager::res8Clicked()
{
    if(selimg.isNull()) return;
    capt[7]=true;
    resimg[7]=selimg.copy();
    resSize=selimg.size();
    ui->resLabel8->setPixmap(selimg.scaled(ui->resLabel8->size(),Qt::KeepAspectRatio));
}

void Imager::res9Clicked()
{
    if(selimg.isNull()) return;
    capt[8]=true;
    resimg[8]=selimg.copy();
    resSize=selimg.size();
    ui->resLabel9->setPixmap(selimg.scaled(ui->resLabel9->size(),Qt::KeepAspectRatio));
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
    imgFile.setFileName("Result.png");
    imgFile.open(QIODevice::WriteOnly);
    print.save(&imgFile,"PNG");
    imgFile.close();
}
