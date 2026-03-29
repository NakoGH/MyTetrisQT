#ifndef BOARD_H
#define BOARD_H

#include "tetromino.h"
#include <QtGui/qwindowdefs.h>

class Board
{
private:
    int grid[20][10];
    Tetromino focusedTetromino;
    Tetromino nextTetromino;
    bool gameover = false;


public:
    Board();
    int* getMinoPosition();
    bool isColliding();
    void moveDown(int speed);
    void moveSide(int dir);
    void rotate(int dir);
    void lockTetromino();
    void checklines();
};

#endif // BOARD_H
