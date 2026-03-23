#ifndef BOARD_H
#define BOARD_H

#include "tetromino.h"

class Board
{
private:
    Tetromino focusedTetromino;
    Tetromino nextTetromino;


public:
    Board();
    int* getMinoPosition();
};

#endif // BOARD_H
