#ifndef TETROMINO_H
#define TETROMINO_H
#include "constant.h"

class Tetromino
{
private:

    
public:
    Tetromino();

    enum Constant::Carac data;
    int orientation; // entre 0 et 3
    int X;
    int Y;
    
    void moveSide(int dir);
    void moveDown(int speed);
    
    void rotate(int dir);

};

#endif // TETROMINO_H
