#include "imager.h"
#include "ui_imager.h"

Imager::Imager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Imager)
{
    ui->setupUi(this);
    resetImg();
    connect(ui->actionSelect_Folder,SIGNAL(triggered()),this,SLOT(chkFolder()));
    connect(ui->bigLabel,SIGNAL(doubleClicked()),this,SLOT(closeBig()));
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
    resimg[0]=selimg.copy();
    ui->resLabel1->setPixmap(selimg.scaled(ui->resLabel1->size(),Qt::KeepAspectRatio));
}

void Imager::res2Clicked()
{
    if(selimg.isNull()) return;
    resimg[1]=selimg.copy();
    ui->resLabel2->setPixmap(selimg.scaled(ui->resLabel2->size(),Qt::KeepAspectRatio));
}

void Imager::res3Clicked()
{
    if(selimg.isNull()) return;
    resimg[2]=selimg.copy();
    ui->resLabel3->setPixmap(selimg.scaled(ui->resLabel3->size(),Qt::KeepAspectRatio));
}

void Imager::res4Clicked()
{
    if(selimg.isNull()) return;
    resimg[3]=selimg.copy();
    ui->resLabel4->setPixmap(selimg.scaled(ui->resLabel4->size(),Qt::KeepAspectRatio));
}

void Imager::res5Clicked()
{
    if(selimg.isNull()) return;
    resimg[4]=selimg.copy();
    ui->resLabel5->setPixmap(selimg.scaled(ui->resLabel5->size(),Qt::KeepAspectRatio));
}

void Imager::res6Clicked()
{
    if(selimg.isNull()) return;
    resimg[5]=selimg.copy();
    ui->resLabel6->setPixmap(selimg.scaled(ui->resLabel6->size(),Qt::KeepAspectRatio));
}

void Imager::res7Clicked()
{
    if(selimg.isNull()) return;
    resimg[6]=selimg.copy();
    ui->resLabel7->setPixmap(selimg.scaled(ui->resLabel7->size(),Qt::KeepAspectRatio));
}

void Imager::res8Clicked()
{
    if(selimg.isNull()) return;
    resimg[7]=selimg.copy();
    ui->resLabel8->setPixmap(selimg.scaled(ui->resLabel8->size(),Qt::KeepAspectRatio));
}

void Imager::res9Clicked()
{
    if(selimg.isNull()) return;
    resimg[8]=selimg.copy();
    ui->resLabel9->setPixmap(selimg.scaled(ui->resLabel9->size(),Qt::KeepAspectRatio));
}
