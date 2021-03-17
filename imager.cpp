#include "imager.h"
#include "ui_imager.h"

Imager::Imager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Imager)
{
    ui->setupUi(this);
    connect(ui->actionSelect_Folder,SIGNAL(triggered()),this,SLOT(chkFolder()));
    connect(ui->bigLabel,SIGNAL(doubleClicked()),this,SLOT(closeBig()));
    resetImg();
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
    selimg=label->orig;
    prev->setFrameStyle(QFrame::NoFrame);
    label->setFrameStyle(QFrame::Panel|QFrame::Raised);
    prev=label;
}
