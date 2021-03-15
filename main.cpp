#include "imager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    imager w;
    w.show();
    return a.exec();
}
