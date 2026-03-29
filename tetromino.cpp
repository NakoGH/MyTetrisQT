#include "tetromino.h"

Tetromino::Tetromino() {}


void Tetromino::rotate(int dir)
{
    orientation = (orientation + dir) % 4;
}
