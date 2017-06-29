#include "tile.h"

tile::tile(QString url, int r, int c)
{
    setPixmap(QPixmap(url));
    row=r;
    col=c;
    isFree=false;
    freePos=4;
    setAcceptHoverEvents(true);
    anim=new QPropertyAnimation(this,"pos");
    anim->setDuration(200);
    connect(anim,SIGNAL(finished()),this,SLOT(animfinished()));

    c1=new QGraphicsColorizeEffect();
    c1->setColor(QColor(176,74,69));
    c1->setStrength(0.4);
    c1->setEnabled(false);
    setGraphicsEffect(c1);
}

void tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    slide(1);
}

void tile::slide(int s)
{
    if(isFree)
    {
        if(s==1)
            anim->setStartValue(QPoint(x(),y()));
        switch(freePos)
        {
        case 0:
            if(s==1)
                anim->setEndValue(QPoint(x(),y()-100));
            else if(s==0)
                this->setPos(x(),y()-100);
            break;
        case 1:
            if(s==1)
                anim->setEndValue(QPoint(x()+100,y()));
            else if(s==0)
                this->setPos(x()+100,y());
            break;
        case 2:
            if(s==1)
                anim->setEndValue(QPoint(x(),y()+100));
            else if(s==0)
                this->setPos(x(),y()+100);
            break;
        case 3:
            if(s==1)
                anim->setEndValue(QPoint(x()-100,y()));
            else if(s==0)
                this->setPos(x()-100,y());
            break;
        }
        if(s==1)
        {
            anim->setEasingCurve(QEasingCurve::OutBack);
            anim->start();
        }
        else if(s==0)
            emit slided(freePos);
    }
}

void tile::setFree(int pos)
{
    if(pos<4)
    {
        isFree=true;
        freePos=pos;
    }
}

void tile::lockTile()
{
    isFree=false;
    freePos=4;
}

int tile::status()
{
    return freePos;
}

void tile::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(isFree)
    {
        c1->setEnabled(true);
    }
}

void tile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    c1->setEnabled(false);
}

void tile::animfinished()
{
    emit slided(freePos);
}

