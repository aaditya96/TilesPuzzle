#include "option.h"
#include "QFont"
#include "QGraphicsTextItem"
#include "QGraphicsSceneMouseEvent"
#include "QBrush"

option::option(QString t)
{
   setRect(0,0,200,50);
   QBrush brush;
   brush.setStyle(Qt::SolidPattern);
   brush.setColor(Qt::darkCyan);
   setBrush(brush);

   text=new QGraphicsTextItem(t,this);
   int xpos=(rect().width()/2)-((text->boundingRect().width())/2);
   int ypos=(rect().height()/2)-((text->boundingRect().height())/2);
   text->setFont(QFont("times",15));
   text->setPos(xpos,ypos);

   anim1=new QPropertyAnimation(this,"opacity");
   anim1->setDuration(800);
   anim1->setStartValue(0);
   anim1->setEndValue(1);
   anim1->start();

   setTransformOriginPoint(QPoint(x()+100,y()+25));
   anim2=new QPropertyAnimation(this,"scale");
   anim2->setDuration(800);
   anim2->setStartValue(2);
   anim2->setEndValue(1);
   anim2->start();

   setAcceptHoverEvents(true);
}

void option::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void option::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

void option::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}

