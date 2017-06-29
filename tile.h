#ifndef TILE_H
#define TILE_H
#include "QGraphicsPixmapItem"
#include "QGraphicsSceneMouseEvent"
#include "QPropertyAnimation"
#include "QGraphicsColorizeEffect"

class tile: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    int row,col;
    bool isFree;
    int freePos;
    QPropertyAnimation *anim;
    QGraphicsColorizeEffect *c1;
public:
    tile(QString url,int r,int c);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void slide(int s=0);
    void setFree(int pos);
    void lockTile();
    int status();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void slided(int dir);
public slots:
    void animfinished();
};

#endif // TILE_H
