#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    connect(ui->startBrowse,SIGNAL(clicked()),this,SLOT(startBrowse()));
    connect(ui->saveBrowse,SIGNAL(clicked()),this,SLOT(saveBrowse()));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accepting()));
}

SettingDialog::~SettingDialog()
{
    delete ui;
}
void SettingDialog::startBrowse()
{
    dir=new QDir(QFileDialog::getExistingDirectory(this,"Select Folder",ui->startDire->text()));
    ui->startDire->setText(dir->absolutePath());
}

void SettingDialog::saveBrowse()
{
    dir=new QDir(QFileDialog::getExistingDirectory(this,"Select Folder",ui->saveDire->text()));
    ui->saveDire->setText(dir->absolutePath());
}

void SettingDialog::accepting()
{
    emit setComplete(ui->startDire->text(),ui->nameEdit->text(),ui->pngBtn->isChecked(),ui->saveDire->text());
}
