#ifndef MAZEMODEL_H
#define MAZEMODEL_H

#include <QObject>
#include <QTimer>
#include <QLabel>
#include <QTextStream>

class MazeModel : public QObject
{
    Q_OBJECT
public:
    MazeModel();
    ~MazeModel();
    int getField(int x, int y); // játékmező lekérdezése
    bool stepGame(int x, int y);
    bool isGameOver();
    int playerX;  //játékos x koordinája
    int playerY;  //játékos y koordinája

    /* struct Player{
        int x;
        int y;
    };*/

public slots:
    void newGame(int size, QTextStream* str);  //új játék
    void pauseGame(); // játék szüneteltetése

private slots:
    void updateTime(); //időzítő eseménykezelője

signals:
    void messageChanged(QString message); //üzenetváltás eseménye
private:
    void loadData(int meret, QTextStream* stream);
    int _gameTime;
    int _previewTime;

    QLabel* _timeLabel;
    QTimer* _timer;
    int** table;
    int tableSize;


};

#endif // MAZEMODEL_H
