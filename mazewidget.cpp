#include <QFileDialog>
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

    _pauseButton = new QPushButton(trUtf8("Szünet "));
    _pauseButton->setEnabled(false);
    connect(_pauseButton, SIGNAL(clicked()), _model, SLOT(pauseGame()));
    connect(_pauseButton, SIGNAL(clicked()), this, SLOT(pauseGame()));

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

    if(onLoad())
    {

        //QMessageBox::information(this, "Text", "True!");
        if (QObject::sender() == _smallGameButton)  //attól föggően, mely gombra kattintunk
        {
            _model->newGame(4, _stream);
            _buttonTable.resize(4);
            for(int i=0; i<4; ++i){
                _buttonTable[i].resize(4);
            }
        }
        else if (QObject::sender() == _middleGameButton)
        {
            _model->newGame(8, _stream);
            _buttonTable.resize(8);
            for(int i=0; i<8; ++i){
                _buttonTable[i].resize(8);
            }
        }
        else
        {
            _model->newGame(16, _stream);
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
                _buttonTable[i][j]->setFont(QFont("Times New Roman", 30, QFont::Bold));
                //_buttonTable[i][j]->setFixedSize(45, 45);
                _buttonTable[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
                //_buttonTable[i][j]->setFocusPolicy(Qt::NoFocus);
                _buttonTable[i][j]->setStyleSheet("background-color: grey");
                _tableLayout->addWidget(_buttonTable[i][j], i, j); // gombok felvétele az elhelyezésbe

                connect(_buttonTable[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
            }
        }
    }
    else
    {
        QMessageBox::information(this, "Text",
        "Sikertele file beolvasás. Új játékot a fenti gomb valamelyikével indíthat megfelelő file kiválasztásával!");
    }
    torchLight();
}

void MazeWidget::pauseGame()
{
   if(_pauseButton->text()=="Szünet ")
       _pauseButton->setText(trUtf8("Folytat"));
   else
       _pauseButton->setText(trUtf8("Szünet "));

   if(_buttonTable[0][0]->isEnabled())
   {
       for(int i=0; i<_buttonTable.size(); ++i)
       {
           for(int j=0; j<_buttonTable.size(); ++j)
           {
               _buttonTable[i][j]->setEnabled(false);
           }
       }
   }
   else
   {
       for(int i=0; i<_buttonTable.size(); ++i)
       {
           for(int j=0; j<_buttonTable.size(); ++j)
           {
               _buttonTable[i][j]->setEnabled(true);
           }
       }
    }
}

bool MazeWidget::onLoad()
{
    QString filename = QFileDialog::getOpenFileName(this,"Save doument",
        QString(tr("/Users/tibi-macbook/Desktop/Qt/labirintus")), "*.txt" );
        //QDir::currentPath(), "*.txt" );
    QFile file( filename );
    if(file.open(QIODevice::ReadOnly))
    {
        _stream = new QTextStream(&file);
        return true;
        //QString text = stream.readAll();

        //QMessageBox::information(this, "Text", text);
    }
    else return false;
}

void MazeWidget::buttonClicked()
{
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = _tableLayout->indexOf(senderButton);

    int s = _buttonTable.size();
    int x = location/s;
    int y = location%s;
    if(_model->stepGame(x,y))
    {
        //_buttonTable[x][y]->setStyleSheet("background-color: red");
        //_buttonTable[x][y]->setText("O");
        torchLight();
    }
}

void MazeWidget::torchLight()
{
    int x=-1;
    int y=-1;
    int playerX=_model->playerX;
    int playerY=_model->playerY;
    int s = _buttonTable.size();

    for(int i=0; i<s; ++i)
    {
        for(int j=0; j<s; ++j)
        {
            _buttonTable[i][j]->setStyleSheet("background-color: grey");
            _buttonTable[i][j]->setText("");
        }
    }

    if(_model->getField(playerX,playerY) == 0)
    {
        _buttonTable[playerX][playerY]->setText("O");
        x=playerX;
        y=playerY;
    }
    if(x!=-1 && y!=-1)
    {
    if( y+1<s && _model->getField(x,y+1) == 1)
        _buttonTable[x][y+1]->setStyleSheet("background-color: yellow");
    else if(y+1<s && _model->getField(x,y+1) == 2)
        _buttonTable[x][y+1]->setStyleSheet("background-color: black");
    if( y+2<s && _model->getField(x,y+1) != 2 && _model->getField(x,y+2) == 1)
        _buttonTable[x][y+2]->setStyleSheet("background-color: orange");
    else if(y+2<s && _model->getField(x,y+1) != 2 && _model->getField(x,y+2) == 2)
        _buttonTable[x][y+2]->setStyleSheet("background-color: black");
    if( x+1<s && _model->getField(x+1,y) == 1)
        _buttonTable[x+1][y]->setStyleSheet("background-color: yellow");
    else if( x+1<s && _model->getField(x+1,y) == 2)
        _buttonTable[x+1][y]->setStyleSheet("background-color: black");
    if( x+2<s && _model->getField(x+2,y) == 1 && _model->getField(x+1,y) == 1)
        _buttonTable[x+2][y]->setStyleSheet("background-color: orange");
    else if( x+2<s && _model->getField(x+2,y) == 2 && _model->getField(x+1,y) == 1)
        _buttonTable[x+2][y]->setStyleSheet("background-color: black");
    if( x-1>=0 && _model->getField(x-1,y) == 1)
        _buttonTable[x-1][y]->setStyleSheet("background-color: yellow");
    else if( x-1>=0 && _model->getField(x-1,y) == 2)
        _buttonTable[x-1][y]->setStyleSheet("background-color: black");
    if( x-2>=0 && _model->getField(x-1,y) == 1 && _model->getField(x-2,y) == 1)
        _buttonTable[x-2][y]->setStyleSheet("background-color: orange");
    else if( x-2>=0 && _model->getField(x-1,y) == 1 && _model->getField(x-2,y) == 2)
        _buttonTable[x-2][y]->setStyleSheet("background-color: black");
    if( y-1>=0 && _model->getField(x,y-1) == 1)
        _buttonTable[x][y-1]->setStyleSheet("background-color: yellow");
    else if( y-1>=0 && _model->getField(x,y-1) == 2)
        _buttonTable[x][y-1]->setStyleSheet("background-color: black");
    if( y-2>=0 && _model->getField(x,y-1) == 1 && _model->getField(x,y-2) == 1)
        _buttonTable[x][y-2]->setStyleSheet("background-color: orange");
    else if( y-2>=0 && _model->getField(x,y-1) == 1 && _model->getField(x,y-2) == 2)
        _buttonTable[x][y-2]->setStyleSheet("background-color: black");

    }
    if(_model->isGameOver())
    //if(playerX==0 && playerY==(_buttonTable[0].size()-1))
    {
        QMessageBox::information(this, trUtf8("Játék vége!"), trUtf8("Gratulálok!\n Kérem kezdjen új játékot!"));
        _buttonTable[0][_buttonTable.size()-1]->setStyleSheet("background-color: red");

    }
}
