#ifndef MAZEMODEL_H
#define MAZEMODEL_H

#include <QObject>
#include <QTimer>
#include <QLabel>


class MazeModel : public QObject
{
    Q_OBJECT
public:
    MazeModel();
    ~MazeModel();
    int getField(int x, int y); // játékmező lekérdezése
public slots:
    void newGame(int size);  //új játék

private slots:
    void updateTime(); //időzítő eseménykezelője

signals:
    void messageChanged(QString message); //üzenetváltás eseménye
private:
    int _gameTime;
    int _previewTime;

    QLabel* _timeLabel;
    QTimer* _timer;
    int** table;
};

#endif // MAZEMODEL_H
