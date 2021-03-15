#include "imager.h"
#include "ui_imager.h"

imager::imager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::imager)
{
    ui->setupUi(this);
}

imager::~imager()
{
    delete ui;
}

