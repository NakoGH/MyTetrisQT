#include "tetromino.h"
#include <cstdlib>
#include <ctime>

const Shape Tetromino::s_shapes[7][4] = {

// I  (cyan)
{
    Shape{{{0,1},{1,1},{2,1},{3,1}}},   // 0°
    Shape{{{2,0},{2,1},{2,2},{2,3}}},   // 90°
    Shape{{{0,2},{1,2},{2,2},{3,2}}},   // 180°
    Shape{{{1,0},{1,1},{1,2},{1,3}}},   // 270°
},

    // O  (jaune)
    {
     Shape{{{1,0},{2,0},{1,1},{2,1}}},
     Shape{{{1,0},{2,0},{1,1},{2,1}}},
     Shape{{{1,0},{2,0},{1,1},{2,1}}},
     Shape{{{1,0},{2,0},{1,1},{2,1}}},
     },

    // T  (violet)
    {
     Shape{{{1,0},{0,1},{1,1},{2,1}}},
     Shape{{{1,0},{1,1},{2,1},{1,2}}},
     Shape{{{0,1},{1,1},{2,1},{1,2}}},
     Shape{{{1,0},{0,1},{1,1},{1,2}}},
     },

    // S  (vert)
    {
     Shape{{{1,0},{2,0},{0,1},{1,1}}},
     Shape{{{1,0},{1,1},{2,1},{2,2}}},
     Shape{{{1,1},{2,1},{0,2},{1,2}}},
     Shape{{{0,0},{0,1},{1,1},{1,2}}},
     },

    // Z  (rouge)
    {
     Shape{{{0,0},{1,0},{1,1},{2,1}}},
     Shape{{{2,0},{1,1},{2,1},{1,2}}},
     Shape{{{0,1},{1,1},{1,2},{2,2}}},
     Shape{{{1,0},{0,1},{1,1},{0,2}}},
     },

    // J  (bleu)
    {
     Shape{{{0,0},{0,1},{1,1},{2,1}}},
     Shape{{{1,0},{2,0},{1,1},{1,2}}},
     Shape{{{0,1},{1,1},{2,1},{2,2}}},
     Shape{{{1,0},{1,1},{0,2},{1,2}}},
     },

    // L  (orange)
    {
        Shape{{{2,0},{0,1},{1,1},{2,1}}},
        Shape{{{1,0},{1,1},{1,2},{2,2}}},
        Shape{{{0,1},{1,1},{2,1},{0,2}}},
        Shape{{{0,0},{1,0},{1,1},{1,2}}},
        },
    };


Tetromino::Tetromino(Type type) {
    m_type = type;
    m_rotation = 0;
    x = 3;
    y = 0;
}


Shape Tetromino::blocks() const{
    if (m_type == Type::None)
        return Shape{{{0,0},{0,0},{0,0},{0,0}}};
    return s_shapes[static_cast<int>(m_type)][m_rotation];
}


Shape Tetromino::absoluteBlocks() const {
    Shape abs = blocks();
    for (auto& b : abs) {
        b.x += x;
        b.y += y;
    }
    return abs;
}

void Tetromino::rotateRight()
{
    m_rotation = (m_rotation + 1) % 4;
}


void Tetromino::rotateLeft()
{
    m_rotation = (m_rotation + 3) % 4;
}



QColor Tetromino::colorOf(Type type)
{
    switch (type) {
    case Type::I: return QColor(0x00CFCF); // cyan
    case Type::O: return QColor(0xF0C000); // jaune
    case Type::T: return QColor(0xA000F0); // violet
    case Type::S: return QColor(0x00A000); // vert
    case Type::Z: return QColor(0xF00000); // rouge
    case Type::J: return QColor(0x0000F0); // bleu
    case Type::L: return QColor(0xF0A000); // orange
    default:
        return QColor("black");
    }
}

Tetromino Tetromino::random()
{
    // Initialise le seed pour l'aléatoire une seule fois
    static bool seeded = false;
    if (!seeded) { std::srand(std::time(nullptr)); seeded = true; }

    int idx = std::rand() % 7;
    return Tetromino(static_cast<Type>(idx));
}