#ifndef IMAGER_H
#define IMAGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class imager; }
QT_END_NAMESPACE

class imager : public QMainWindow
{
    Q_OBJECT

public:
    imager(QWidget *parent = nullptr);
    ~imager();

private:
    Ui::imager *ui;
};
#endif // IMAGER_H
