#include "tetromino.h"

Tetromino::Tetromino() {}

void Tetromino::moveSide(int dir=1)
{
    X += dir;

}

void Tetromino::moveDown(int speed=1)
{
    Y += speed;

}

void Tetromino::rotate(int dir)
{
    orientation = (orientation + dir) % 4;
}
