#include <QMessageBox>
#include "mazewidget.h"

MazeWidget::MazeWidget(QWidget *parent): QWidget(parent)
{
    setMinimumSize(600,600);
    setBaseSize(600,600);
    setWindowTitle(trUtf8("Labirintus"));

    _model = new MazeModel();

    _smallGameButton = new QPushButton(trUtf8("Könnyű játék (4)"));
    connect(_smallGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
    _middleGameButton = new QPushButton(trUtf8("Közepes játék (8)"));
    connect(_middleGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
    _largeGameButton = new QPushButton(trUtf8("Nehéz játék (16)"));
    connect(_largeGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));

    _pauseButton = new QPushButton(trUtf8("Szünet"));
    _pauseButton->setEnabled(false);
    //connect(_pauseButton, SIGNAL(clicked()), _model, SLOT(pauseGame()));

    _messageLabel = new QLabel(trUtf8("Játék kezdése"));
    connect(_model, SIGNAL(messageChanged(QString)), _messageLabel, SLOT(setText(QString)));


    _toolLayout = new QHBoxLayout();
    _toolLayout->addWidget(_smallGameButton);
    _toolLayout->addWidget(_middleGameButton);
    _toolLayout->addWidget(_largeGameButton);
    _toolLayout->addWidget(_messageLabel);
    _toolLayout->addWidget(_pauseButton);

    _mainLayout = new QVBoxLayout();
    _mainLayout->addLayout(_toolLayout);

    _tableLayout = new QGridLayout();
    _mainLayout->addLayout(_tableLayout);

    setLayout(_mainLayout);

}

MazeWidget::~MazeWidget()
{
    delete _model;
}

void MazeWidget::startNewGame(){
    //előző tábla törlése
    foreach(QVector<QPushButton*> rows, _buttonTable){
       foreach(QPushButton* button, rows){
          _tableLayout->removeWidget(button);
          delete button;
       }
    }
    _buttonTable.clear();

    if (QObject::sender() == _smallGameButton)  //attól föggően, mely gombra kattintunk
    {
        _model->newGame(4);
        _buttonTable.resize(4);
        for(int i=0; i<4; ++i){
            _buttonTable[i].resize(4);
        }
    }
    else if (QObject::sender() == _middleGameButton)
    {
        _model->newGame(8);
        _buttonTable.resize(8);
        for(int i=0; i<8; ++i){
            _buttonTable[i].resize(8);
        }
    }
    else
    {
        _model->newGame(16);
        _buttonTable.resize(16);
        for(int i=0; i<16; ++i){
            _buttonTable[i].resize(16);
        }
    }
    _pauseButton->setEnabled(true); //már lehet szüneteltetni

    for (int i = 0; i < _buttonTable.size(); ++i)
    {
        for (int j = 0; j < _buttonTable[i].size(); ++j)
        {
            _buttonTable[i][j]= new QPushButton(this);
            _buttonTable[i][j]->setFont(QFont("Times New Roman", 60, QFont::Bold));
            _buttonTable[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            _tableLayout->addWidget(_buttonTable[i][j], i, j); // gombok felvétele az elhelyezésbe

            //connect(buttonTable[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }

}


