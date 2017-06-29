#include "timer.h"
#include "QFont"

Timer::Timer(int tot)
{
    time=tot;
    setPlainText("Time Left:"+QString::number(time));
    setDefaultTextColor(Qt::darkRed);
    setFont(QFont("comic sans",20));
    setPos(50,350);
}

void Timer::decrement()
{
    if(time>0)
        time--;
    setPlainText("Time Left:"+QString::number(time));
    if(time==0)
        emit timeup();
}
