#include "imager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Strabismus Imager");
    Imager w;
    w.show();
    return a.exec();
}
