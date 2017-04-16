#include "mazemodel.h"

MazeModel::MazeModel()
{

}

/*void MazeModel::pauseGame()
{
    if (_previewTime > 0 || _gameTime >= _gameLength)
        return;

    if (_timer->isActive()) // ha megy az időzítő
    {
        messageChanged(trUtf8("Pihi van."));
        _timer->stop(); // leállítjuk
    }
    else
        _timer->start(); // különben elindít
}*/

void MazeModel::newGame(int size)
{
    for (int i = 0; i < size; ++i)
    {
        //gameTable[i] = new int[3];
        for (int j = 0; j < size; ++j)
        {
            table[i][j]= 1;

        }
    }
}
