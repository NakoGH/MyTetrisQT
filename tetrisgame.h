#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "tetromino.h"
#include <QObject>
#include <QTimer>
#include <QtQml/qqmlregistration.h>
// #include "tetrisbboard.h"

class TetrisGame
{
public:
    TetrisGame();

    void moveLeft();
    void moveRight();
    void softDrop();
    void hardDrop();
    
private:
    // TetrisBoard board;
    Tetromino current;
    Tetromino hold;
    Tetromino next;

    QTimer* timer;
    
    void tryMove(int dx, int dy);


    void tick();
};
#endif // TETRISGAME_H
