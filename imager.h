#ifndef IMAGER_H
#define IMAGER_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QRubberBand>
#include <QDebug>
#include <QStyle>
#include <QPainter>
#include <QSettings>
#include "clickablelabel.h"
#include "settingdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Imager; }
QT_END_NAMESPACE

class Imager : public QMainWindow
{
    Q_OBJECT

public:
    Imager(QWidget *parent = nullptr);
    ~Imager();
    bool coord=false;

public slots:
    void chkFolder();

private slots:
    void sendBig(ClickableLabel *label);
    void resetImg();
    void closeBig();
    void selection(ClickableLabel *label,QPoint point);
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
    void dragging(ClickableLabel *label,QPoint point);
    void dragComp(ClickableLabel *label,QPoint point);
    void keyPressEvent(QKeyEvent *event);
    void res1Dragged();
    void res2Dragged();
    void res3Dragged();
    void res4Dragged();
    void res5Dragged();
    void res6Dragged();
    void res7Dragged();
    void res8Dragged();
    void res9Dragged();
    void settings();
    void doneSetting(QString startDirectory,QString fileName,bool isPNG,QString saveDirectory);

signals:
    void filterAll(int sx,int sy,int ex,int ey,int bw,int bh);
    void resetAll();

private:
    Ui::Imager *ui;
    QDir *dir,startdir,savedir;
    QStringList list;
    QPixmap defimg,selimg,resimg[9];
    int mrow=0,mcol=0,max=0,stx=0,sty=0,enx=0,eny=0,count=0;
    bool capt[9]={false},ispng=true;
    ClickableLabel *prev;
    SettingDialog *setdia=new SettingDialog(this);
    QSize resSize;
    QPainter painter;
    QFile imgFile;
    QRect selRect;
    QPoint start,end;
    QSettings sett;
    QString fileName="NineCardinal";
};
#endif // IMAGER_H
