#ifndef TETROMINO_H
#define TETROMINO_H
#include "constant.h"

class Tetromino
{
private:
    enum Constant::Carac data;
    int orientation;
    int rotationCenterX;
    int rotationCenterY;

public:
    Tetromino();

    void moveSide(int dir);
    void moveDown(int speed);
    void rotate(int dir);

};

#endif // TETROMINO_H
