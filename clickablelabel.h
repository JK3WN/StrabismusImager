#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QDebug>
#include <QPainter>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent=Q_NULLPTR,Qt::WindowFlags f=Qt::WindowFlags());
    ~ClickableLabel();
    int ro=-1,co=-1,type=0,adjust=-1;
    bool drag=false,down=false;
    QPixmap orig,small;
    QPainter painter;
    QPoint start,end,dragStart;
    QRect origRect,bigRect,smallRect;
    QPixmap sendPixmap();
    QSize sizee;

signals:
    void clicked();
    void nclicked(ClickableLabel *label,QPoint point);
    void doubleClicked();
    void ndoubleClicked(ClickableLabel *label);
    void sendCoords(int sx,int sy,int ex,int ey);
    void dragEnd();
    void ndragged(ClickableLabel *label,QPoint point);
    void ndragEnd(ClickableLabel *label,QPoint point);

public slots:
    void filtered(int sx,int sy,int ex,int ey,int bw,int bh);
    void resetFilter();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool event(QEvent *e);
    void hoverMove(QHoverEvent *event);
};

#endif // CLICKABLELABEL_H
