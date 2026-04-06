#ifndef TETROMINO_H
#define TETROMINO_H
#include "constant.h"
#include <QColor>

class Tetromino
{
private:

    
public:
    Tetromino();

    enum Constant::Carac data;
    int orientation;
    int X;
    int Y;
    
    void moveSide(int dir);
    void moveDown(int speed);
    
    void rotate(int dir);

    QColor colorof(Constant::Carac type);

};

#endif // TETROMINO_H
