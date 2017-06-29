#include "puzzle.h"
#include "QBrush"
#include "QGraphicsTextItem"
#include "option.h"
#include "QFont"
#include "QTime"
#include "QCoreApplication"
#include "QEventLoop"

puzzle::puzzle()
{
    initialise();
}

void puzzle::initialise()
{
    scene=new QGraphicsScene();
    scene->setSceneRect(0,0,1000,700);
    setScene(scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1000,700);

    setBackgroundBrush(QBrush(QImage(":/new/background/Images/bg2.jpg")));

    tilearray[0]=new tile(":/new/easy/Images/Easy/3x3_1.jpg",1,1);
    tilearray[1]=new tile(":/new/easy/Images/Easy/3x3_2.jpg",1,2);
    tilearray[2]=new tile(":/new/easy/Images/Easy/3x3_3.jpg",1,3);
    tilearray[3]=new tile(":/new/easy/Images/Easy/3x3_4.jpg",2,1);
    tilearray[4]=new tile(":/new/easy/Images/Easy/3x3_5.jpg",2,2);
    tilearray[5]=new tile(":/new/easy/Images/Easy/3x3_6.jpg",2,3);
    tilearray[6]=new tile(":/new/easy/Images/Easy/3x3_7.jpg",3,1);
    tilearray[7]=new tile(":/new/easy/Images/Easy/3x3_8.jpg",3,2);
    tilearray[8]=new tile(":/new/easy/Images/Easy/3x3_9.jpg",3,3);

    img=new QGraphicsPixmapItem();
    img->setPixmap(QPixmap(":/new/background/Images/Original.jpg"));
    img->setPos(750,300);

    freetile=new QGraphicsRectItem(0,0,100,100);

    for(int i=0;i<9;i++)
    {
        connect(tilearray[i],SIGNAL(slided(int)),this,SLOT(SlotSlided(int)));
    }

    shuffling=completed=hard=false;
}

void puzzle::DisplayMenu()
{
    initialise();
    QGraphicsTextItem *title=new QGraphicsTextItem();
    title->setPlainText("Sliding Tiles");
    title->setDefaultTextColor(Qt::green);
    title->setFont(QFont("comic sans",60));
    title->setPos(300,100);

    option *easy=new option("Easy");
    easy->setPos(400,300);
    connect(easy,SIGNAL(clicked()),this,SLOT(easymode()));

    option *medium=new option("Medium");
    medium->setPos(400,400);
    connect(medium,SIGNAL(clicked()),this,SLOT(mediummode()));

    option *hard=new option("Hard");
    hard->setPos(400,500);
    connect(hard,SIGNAL(clicked()),this,SLOT(hardmode()));


    scene->addItem(title);
    scene->addItem(easy);
    scene->addItem(medium);
    scene->addItem(hard);

}

void puzzle::setFreeTiles()
{
    for(int i=0;i<9;i++)
    {
        if(tilearray[i]->x()==freetile->x()&&tilearray[i]->y()==(freetile->y()+100))
            tilearray[i]->setFree(0);
        else if(tilearray[i]->x()==(freetile->x()-100)&&tilearray[i]->y()==(freetile->y()))
            tilearray[i]->setFree(1);
        else if(tilearray[i]->x()==freetile->x()&&tilearray[i]->y()==(freetile->y()-100))
            tilearray[i]->setFree(2);
        else if(tilearray[i]->x()==(freetile->x()+100)&&tilearray[i]->y()==(freetile->y()))
            tilearray[i]->setFree(3);
        else
            tilearray[i]->lockTile();
    }
}

void puzzle::easymode()
{
    scene->clear();
    for(int i=0;i<9;i++)
    {
        tilearray[i]->setPos(350+(100*(i%3)),200+(100*(i/3)));
        scene->addItem(tilearray[i]);
    }

    freetile->setPos(550,500);
    scene->addItem(freetile);
    shuffle();

    scene->addItem(img);
}

void puzzle::mediummode()
{
    scene->clear();

    for(int i=0;i<9;i++)
    {
        tilearray[i]->setPos(350+(100*(i%3)),200+(100*(i/3)));
        scene->addItem(tilearray[i]);
    }
    freetile->setPos(550,500);
    scene->addItem(freetile);
    shuffle();

    movetext=new Moves(20);
    connect(movetext,SIGNAL(movesfinished()),this,SLOT(EndGame()));

    for(int i=0;i<9;i++)
    connect(tilearray[i],SIGNAL(slided(int)),movetext,SLOT(increment()));

    scene->addItem(movetext);
    scene->addItem(img);
}

void puzzle::hardmode()
{
    scene->clear();

    hard=true;
    for(int i=0;i<9;i++)
    {
        tilearray[i]->setPos(350+(100*(i%3)),200+(100*(i/3)));
        scene->addItem(tilearray[i]);
    }
    freetile->setPos(550,500);
    scene->addItem(freetile);
    shuffle();

    movetext=new Moves(20);
    connect(movetext,SIGNAL(movesfinished()),this,SLOT(EndGame()));

    for(int i=0;i<9;i++)
    connect(tilearray[i],SIGNAL(slided(int)),movetext,SLOT(increment()));
    scene->addItem(movetext);

    timertext=new Timer(20);

    timer= new QTimer();

    connect(timer,SIGNAL(timeout()),timertext,SLOT(decrement()));
    connect(timertext,SIGNAL(timeup()),this,SLOT(EndGame()));

    for(int i=0;i<9;i++)
    connect(tilearray[i],SIGNAL(slided(int)),this,SLOT(startTimer()));

    scene->addItem(timertext);
    scene->addItem(img);
}

void puzzle::shuffle()
{
    shuffling=true;
    for(int i=0;i<40;i++)
    {
    setFreeTiles();

    QTime dieTime= QTime::currentTime().addMSecs(100);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    QList<tile *> templist;
    for(int j=0;j<9;j++)
    {
        if(tilearray[j]->status()<4)
            templist.append(tilearray[j]);
    }
    int randnumber=rand() % templist.size();
    templist.at(randnumber)->slide();
    }
    setFreeTiles();
    shuffling=false;
}

void puzzle::SlotSlided(int dir)
{
    switch(dir)
    {
    case 0:
        freetile->setPos(freetile->x(),freetile->y()+100);
        break;
    case 1:
        freetile->setPos(freetile->x()-100,freetile->y());
        break;
    case 2:
        freetile->setPos(freetile->x(),freetile->y()-100);
        break;
    case 3:
        freetile->setPos(freetile->x()+100,freetile->y());
        break;
    }
    setFreeTiles();
    if(!shuffling)
    {
        if(freetile->x()==550&&freetile->y()==500)
        {
            completed=true;
            for(int i=0;i<9;i++)
            {
                if(tilearray[i]->x()!=(350+(100*(i%3)))||tilearray[i]->y()!=(200+(100*(i/3))))
                {
                    completed=false;
                    break;
                }
            }
        }
    }
    if(completed)
    {
        EndGame(1);
    }
}

void puzzle::EndGame(int solved)
{
    QGraphicsTextItem *EndText=new QGraphicsTextItem;
    if(solved==1)
    {
        for(int i=0;i<9;i++)
            tilearray[i]->lockTile();

        EndText->setPlainText("Successfully Solved");
        EndText->setDefaultTextColor(Qt::white);
        EndText->setFont(QFont("comic sans",40));
        EndText->setPos(300,50);
        scene->addItem(EndText);
    }
    else
    {
        for(int i=0;i<9;i++)
            tilearray[i]->lockTile();

        EndText->setPlainText("Better Luck Next Time");
        EndText->setDefaultTextColor(Qt::white);
        EndText->setFont(QFont("comic sans",40));
        EndText->setPos(300,50);
        scene->addItem(EndText);
    }
    if(hard)
    {
        disconnect(timer,SIGNAL(timeout()),timertext,SLOT(decrement()));
    }
    option *playagain=new option("Play Again");
    playagain->setPos(400,620);
    connect(playagain,SIGNAL(clicked()),this,SLOT(DisplayMenu()));
    scene->addItem(playagain);

}

void puzzle::startTimer()
{
    if(!timer->isActive())
    {
        timer->start(1000);
    }
}
