#include <QApplication>
#include "puzzle.h"

puzzle * puzzleobj;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    puzzleobj=new puzzle();
    puzzleobj->show();
    puzzleobj->DisplayMenu();

    return a.exec();
}
