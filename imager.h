#ifndef IMAGER_H
#define IMAGER_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QRubberBand>
#include <QDebug>
#include <QStyle>
#include <QPainter>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Imager; }
QT_END_NAMESPACE

class Imager : public QMainWindow
{
    Q_OBJECT

public:
    Imager(QWidget *parent = nullptr);
    ~Imager();

private slots:
    void chkFolder();
    void sendBig(ClickableLabel *label);
    void resetImg();
    void closeBig();
    void selection(ClickableLabel *label);
    void res1Clicked();
    void res2Clicked();
    void res3Clicked();
    void res4Clicked();
    void res5Clicked();
    void res6Clicked();
    void res7Clicked();
    void res8Clicked();
    void res9Clicked();
    void save();

private:
    Ui::Imager *ui;
    QDir *dir;
    QStringList list;
    QPixmap defimg,selimg,resimg[9];
    int mrow=0,mcol=0,max=0;
    bool capt[9]={false};
    ClickableLabel *prev;
    QSize resSize;
    QPainter painter;
    QFile imgFile;
};
#endif // IMAGER_H
