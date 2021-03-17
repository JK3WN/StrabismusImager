#ifndef IMAGER_H
#define IMAGER_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QRubberBand>
#include <QDebug>
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

private:
    Ui::Imager *ui;
    QDir *dir;
    QStringList list;
    QPixmap defimg,selimg;
    int mrow=0,mcol=0;
    ClickableLabel *prev;
};
#endif // IMAGER_H
