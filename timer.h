#ifndef TIMER_H
#define TIMER_H
#include "QGraphicsTextItem"

class Timer:public QGraphicsTextItem
{
    Q_OBJECT
    int time;
public:
    Timer(int tot);
public slots:
    void decrement();
signals:
    void timeup();
};

#endif // TIMER_H
