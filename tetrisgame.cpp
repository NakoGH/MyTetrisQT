#include "tetrisgame.h"

TetrisGame::TetrisGame() {}


void TetrisGame::moveLeft() {
    tryMove(-1, 0);
}

void TetrisGame::moveRight() {
    tryMove(1, 0);
}

void TetrisGame::softDrop() {
    current.moveDown(1);
}


void TetrisGame::tryMove(int dx, int dy) {
    this->current.rotationCenterX += dx;
    this->current.rotationCenterY += dy;
}