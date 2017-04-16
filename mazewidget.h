#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>

#include "mazemodel.h"

class MazeWidget : public QWidget
{
    Q_OBJECT

public:
    MazeWidget(QWidget *parent = 0);
    ~MazeWidget();
};

#endif // MAZEWIDGET_H
