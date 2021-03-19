#include "imager.h"
#include <QSplashScreen>
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Strabismus Imager");
    QPixmap pixmap(":/image/SplashImage.jpg");
    QSplashScreen splash(pixmap.scaled(960,540,Qt::KeepAspectRatio));
    splash.show();
    QTimer::singleShot(2000,&splash,&QWidget::close);
    Imager w;
    QTimer::singleShot(2000,&w,SLOT(show()));
    QTimer::singleShot(2100,&w,SLOT(chkFolder()));
    return a.exec();
}
