#ifndef MAZEMODEL_H
#define MAZEMODEL_H

#include <QObject>


class MazeModel : public QObject
{
    Q_OBJECT
public:
    MazeModel();


public slots:
    void newGame(int size);  //új játék

private slots:
    //void updateTime(); //időzítő eseménykezelője

private:
    //int time;
    //QTimer* _timer;
    int** table;
};

#endif // MAZEMODEL_H
