#ifndef IMAGER_H
#define IMAGER_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QRubberBand>
#include <QDebug>

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
    void addLabel();
    void bugg(int row,int col);
    void resetImg();

private:
    Ui::Imager *ui;
    QDir *dir;
    QStringList list;
    QPixmap defimg;
};
#endif // IMAGER_H
