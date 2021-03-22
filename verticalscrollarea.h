#ifndef VERTICALSCROLLAREA_H
#define VERTICALSCROLLAREA_H

#include <QGridLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QResizeEvent>

class VerticalScrollArea : public QScrollArea
{
public:
    QWidget *content;
    QGridLayout *grid;
    int nRows=3,nColumns=3;
    QPixmap small;

public:
    VerticalScrollArea(QWidget *parent=Q_NULLPTR);
    void addWidget(QWidget *w,int row,int col);
    int rowCount();
    void resetItems();

private:
    void adaptSize();

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // VERTICALSCROLLAREA_H
