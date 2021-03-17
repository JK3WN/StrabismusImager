#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent=Q_NULLPTR,Qt::WindowFlags f=Qt::WindowFlags());
    ~ClickableLabel();
    int ro=-1,co=-1;
    QPixmap orig;
    QPixmap sendPixmap();

signals:
    void clicked();
    void nclicked(ClickableLabel *label);
    void doubleClicked();
    void ndoubleClicked(ClickableLabel *label);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event); 
};

#endif // CLICKABLELABEL_H
