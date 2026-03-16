#include "tetromino.h"

Tetromino::Tetromino() {}

void Tetromino::moveSide(int dir=1)
{
    rotationCenterX = rotationCenterX + dir;

}

void Tetromino::moveDown(int speed=1)
{
    rotationCenterY = rotationCenterY + speed;

}

void Tetromino::rotate(int dir)
{
    orientation = (orientation + dir) % 4;
}
