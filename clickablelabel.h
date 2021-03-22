#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <QRubberBand>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent=Q_NULLPTR,Qt::WindowFlags f=Qt::WindowFlags());
    ~ClickableLabel();
    int ro=-1,co=-1,type=0;
    bool drag=false;
    QPixmap orig,small;
    QPainter painter;
    QRubberBand *rubberBand;
    QPoint start,end,dragStart,startTL;
    QPixmap sendPixmap();

signals:
    void clicked();
    void nclicked(ClickableLabel *label);
    void doubleClicked();
    void ndoubleClicked(ClickableLabel *label);
    void sendCoords(int sx,int sy,int ex,int ey);
    void dragEnd();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // CLICKABLELABEL_H
