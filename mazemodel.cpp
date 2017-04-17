#include "mazemodel.h"

MazeModel::MazeModel()
{
    _timer = new QTimer();
    _timer->setInterval(1000);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    tableSize=0;
}

MazeModel::~MazeModel()
{
    _timer->stop();
    delete _timer;
}

void MazeModel::pauseGame()
{
    if (_timer->isActive()) // ha megy az időzítő
    {
        //messageChanged(trUtf8("Pihi van."));
        _timer->stop(); // leállítjuk
    }
    else
        _timer->start(); // különben elindít
}

void MazeModel::newGame(int size, QTextStream* str)
{
    _timer->start();
    _gameTime=0;
    delete[] table;
    table = new int*[size];
    for (int i = 0; i < size; ++i)
    {
        table[i] = new int[size];
        for (int j = 0; j < size; ++j)
        {
            table[i][j]= 1;
        }
    }
    loadData(size,str);
}

int MazeModel::getField(int x, int y)
{
    return table[x][y];
}

void MazeModel::updateTime()
{
    _gameTime++;
    int min= _gameTime/60;
    int sec= _gameTime % 60;
    _previewTime=_gameTime;
    messageChanged(trUtf8("Eltelt idő: ") + QString::number(min) +
                        tr(":") + QString::number(sec));
}

void MazeModel::loadData(int meret, QTextStream* stream)
{
    /*QTextStream* a = new QTextStream;
    for(int i=0; i<meret; ++i)
    {;
        for(int j=0; j<meret; ++j)
        {
            stream << a;
            if(*a=="1")
            table[i][j]=1;
            else if(*a=="2")
            table[i][j]=2;
            else
            QMessageBox::warning(this, trUtf8("Hiba!"), trUtf8("Nem 1-es vagy 2-es"));
        }
    }*/
    playerX=meret-1;
    playerY=0;
    table[meret-1][0]=0;
    //table[0][meret-1]=3;
    table[meret-1][2]=2;
    tableSize=meret;
}

bool MazeModel::stepGame(int x, int y)
{
    int pX=playerX;
    int pY=playerY;
    if(pX+1<tableSize && (pX+1)==x && pY==y && table[pX+1][pY] == 1)
    {
        table[playerX][playerY]=1;
        playerX=x;
        table[x][y]=0;

        return true;
    }
    else if(pY+1<tableSize && pX==x && (pY+1)==y && table[pX][pY+1] == 1)
    {
        table[playerX][playerY]=1;
        playerY=y;
        table[x][y]=0;

        return true;
    }
    else if(pX-1>=0 && (pX-1)==x && pY==y && table[pX-1][pY] == 1)
    {
        table[playerX][playerY]=1;
        playerX=x;
        table[x][y]=0;

        return true;
    }
    else if(pY-1>=0 && pX==x && (pY-1)==y && table[pX][pY-1] == 1)
    {
        table[playerX][playerY]=1;
        playerY=y;
        table[x][y]=0;

        return true;
    }
    else
        return false;
}

bool MazeModel::isGameOver()
{
    if(playerX==0 && playerY==(tableSize-1))
        return true;
    else
        return false;
}
