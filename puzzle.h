#ifndef PUZZLE_H
#define PUZZLE_H
#include "QGraphicsView"
#include "QObject"
#include "tile.h"
#include "QGraphicsRectItem"
#include "moves.h"
#include "timer.h"
#include "QTimer"
#include "QGraphicsPixmapItem"

class puzzle:public QGraphicsView
{
    Q_OBJECT
    QGraphicsScene *scene;
    tile* tilearray[9];
    QGraphicsRectItem* freetile;
    Moves *movetext;
    Timer *timertext;
    QTimer *timer;
    bool shuffling,completed,hard;
    QGraphicsPixmapItem *img;

public:
    puzzle();
    void initialise();
public slots:
    void DisplayMenu();
    void easymode();
    void mediummode();
    void hardmode();
    void SlotSlided(int dir);
    void EndGame(int solved=0);
    void startTimer();
private:
    void setFreeTiles();
    void shuffle();

};

#endif // PUZZLE_H
