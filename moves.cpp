#include "moves.h"
#include "QFont"

Moves::Moves(int tot)
{
    total=tot;
    moves=0;
    setPlainText("Total Moves:"+QString::number(total)+"\nMoves Played:"+QString::number(moves));
    setDefaultTextColor(Qt::green);
    setFont(QFont("comic sans",20));
    setPos(50,250);
}

void Moves::increment()
{
    if(moves<total)
        moves++;
    setPlainText("Total Moves:"+QString::number(total)+"\nMoves Played:"+QString::number(moves));
    if(moves==total)
        emit movesfinished();
}
