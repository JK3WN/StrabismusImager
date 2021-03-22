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

public slots:
    void chkFolder();

private slots:
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
    void setCoords();

signals:
    void filterAll(int sx,int sy,int ex,int ey);

private:
    Ui::Imager *ui;
    QDir *dir;
    QStringList list;
    QPixmap defimg,selimg,resimg[9];
    int mrow=0,mcol=0,max=0,stx=0,sty=0,enx=0,eny=0;
    bool capt[9]={false},coord=false;
    ClickableLabel *prev;
    QSize resSize;
    QPainter painter;
    QFile imgFile;
};
#endif // IMAGER_H
