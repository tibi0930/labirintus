#ifndef MAZEMODEL_H
#define MAZEMODEL_H

#include <QObject>

class MazeModel : public QObject
{
    Q_OBJECT
public:
    explicit MazeModel(QObject *parent = 0);

signals:

public slots:
};

#endif // MAZEMODEL_H