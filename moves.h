#ifndef MOVES_H
#define MOVES_H
#include "QGraphicsTextItem"

class Moves:public QGraphicsTextItem
{
    Q_OBJECT
    int moves;
    int total;
public:
    Moves(int tot);
signals:
    void movesfinished();
public slots:
    void increment();
};

#endif // MOVES_H
