#include "imager.h"
#include <QSplashScreen>
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Nine Cardinal Positions Image Creator");
    QCoreApplication::setOrganizationName("HVRC");
    QPixmap pixmap(":/image/SplashImage.png");
    QSplashScreen splash(pixmap.scaled(960,540,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    splash.show();
    QTimer::singleShot(1000,&splash,&QWidget::close);
    Imager w;
    QTimer::singleShot(1000,&w,SLOT(show()));
    QTimer::singleShot(1100,&w,SLOT(chkFolder()));
    return a.exec();
}
