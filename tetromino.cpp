#include "tetromino.h"
#include "constant.h"

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

QColor Tetromino::colorOf(Constant::Carac type)
{
    switch (type) {
        case Constant::Carac::I: return QColor(0x00CFCF); // cyan
        case Constant::Carac::O: return QColor(0xF0C000); // jaune
        case Constant::Carac::T: return QColor(0xA000F0); // violet
        case Constant::Carac::S: return QColor(0x00A000); // vert
        case Constant::Carac::Z: return QColor(0xF00000); // rouge
        case Constant::Carac::J: return QColor(0x0000F0); // bleu
        case Constant::Carac::L: return QColor(0xF0A000); // orange
        default:
            return QColor("black");
    }
}
