#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTextStream>
#include "mazemodel.h"

class MazeWidget : public QWidget
{
    Q_OBJECT

public:
    MazeWidget(QWidget *parent = 0);
    ~MazeWidget();

private slots:
    void startNewGame();
    void changeText();

private:
    bool onLoad();
    QTextStream* _stream;
    QGridLayout* _tableLayout;
    QHBoxLayout* _toolLayout;
    QVBoxLayout* _mainLayout;
    QLabel* _messageLabel;
    QPushButton* _smallGameButton;  //új játék gombja
    QPushButton* _middleGameButton;
    QPushButton* _largeGameButton;
    QPushButton* _pauseButton;
    QVector<QVector<QPushButton*> > _buttonTable; //gombtábla

    MazeModel* _model; //a játékot megvalósító modell
};

#endif // MAZEWIDGET_H
