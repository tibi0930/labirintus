#include "mazemodel.h"

MazeModel::MazeModel()
{
    _timer = new QTimer();
    _timer->setInterval(1000);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateTime()));

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

void MazeModel::newGame(int size)
{
    _timer->start();
    _gameTime=0;
    table = new int*[size];
    for (int i = 0; i < size; ++i)
    {
        table[i] = new int[size];
        for (int j = 0; j < size; ++j)
        {
            table[i][j]= -1;
        }
    }

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


