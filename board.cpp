#include "board.h"

Board::Board()
{
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            grid[y][x] = 0;
        }
    }

    //creation des dominos focus et next
}

int* Board::getMinoPosition()
{
    static const int shapes[7][4][8] = {
                                        // I
                                        { {-1,0, 0,0, 1,0, 2,0}, {1,-1, 1,0, 1,1, 1,2}, {-1,1, 0,1, 1,1, 2,1}, {0,-1, 0,0, 0,1, 0,2} },
                                        // O
                                        { {0,0, 1,0, 0,1, 1,1}, {0,0, 1,0, 0,1, 1,1}, {0,0, 1,0, 0,1, 1,1}, {0,0, 1,0, 0,1, 1,1} },
                                        // T
                                        { {-1,0, 0,0, 1,0, 0,1}, {0,-1, 0,0, 0,1, -1,0}, {-1,0, 0,0, 1,0, 0,-1}, {0,-1, 0,0, 0,1, 1,0} },
                                        // S
                                        { {-1,0, 0,0, 0,1, 1,1}, {0,1, 0,0, 1,0, 1,-1}, {-1,-1, 0,-1, 0,0, 1,0}, {-1,1, -1,0, 0,0, 0,-1} },
                                        // Z
                                        { {0,0, 1,0, -1,1, 0,1}, {0,-1, 0,0, 1,0, 1,1}, {0,-1, 1,-1, -1,0, 0,0}, {-1,-1, -1,0, 0,0, 0,1} },
                                        // J
                                        { {-1,0, 0,0, 1,0, -1,1}, {0,-1, 0,0, 0,1, -1,-1}, {-1,0, 0,0, 1,0, 1,-1}, {0,-1, 0,0, 0,1, 1,1} },
                                        // L
                                        { {-1,0, 0,0, 1,0, 1,1}, {0,-1, 0,0, 0,1, -1,1}, {-1,0, 0,0, 1,0, -1,-1}, {0,-1, 0,0, 0,1, 1,-1} },
                                        };

    int* positions = new int[8];

    const int* o = shapes[focusedTetromino.data][focusedTetromino.orientation];

    for (int i = 0; i < 4; ++i)
    {
        positions[2*i] = focusedTetromino.X + o[i*2];
        positions[2*i+1] = focusedTetromino.Y + o[i*2+1];
    }
    return positions;
}

bool Board::isColliding()
{
    int* posi = getMinoPosition();
    for(int i = 0; i<4; i++)
    {
        int nx = posi[2*i];
        int ny = posi[2*i + 1];

        if (nx < 0 || nx >= 10)   return true;

        if (ny < 0 || ny >= 20)   return true;

        if (grid[ny][nx] != 0)    return true;
    }

    return false;
}

void Board::moveSide(int dir) {
    focusedTetromino.X += dir;

    if (isColliding())
        focusedTetromino.X -= dir;
}

void Board::moveDown(int speed) {
    focusedTetromino.Y += speed;

    if (isColliding()) {
        focusedTetromino.Y -= speed;
        lockTetromino();
    }
}

void Board::rotate(int dir) {
    int oldOrientation = focusedTetromino.orientation;

    focusedTetromino.orientation = (focusedTetromino.orientation + dir + 4) % 4;

    if (isColliding())
        focusedTetromino.orientation = oldOrientation;
}


void Board::lockTetromino()
{
    int* posi = getMinoPosition();

    for(int i = 0; i<4; i++)
    {
        int x = posi[2*i];
        int y = posi[2*i + 1];

        grid[y][x] = focusedTetromino.data;
    }

    checklines();

    focusedTetromino = nextTetromino;
    //Creation nv nextDomino

    if (isColliding())
    {
        gameover = true;
    }
}

void Board::checklines()
{
    bool changed = false;

    for(int i = 19; i>=0; i--)
    {
        bool full = true;
        for (int j=0; i<10; j++)
        {
            if(grid[i][j] == 0)
            {
                full=false;
                break;
            }
        }

        if (full)
        {
            changed = true;

            for(int row=i; row>0; row--)
            {
                for(int j=0; j<10; j++)
                {
                    grid[row][j] = grid[row-1][j];
                }
            }

            i++;
        }
    }

    if (changed)
    {
        for(int i=0; i<0; i++)
        {
            grid[0][i] = 0;
        }
    }
}
