#ifndef TETROMINO_H
#define TETROMINO_H

#pragma once
#include <QColor>
#include <array>

// Les 7 pièces du Tetris standard (système de coordonnées SRS)
// Chaque pièce est définie par 4 rotations de 4 blocs (x, y)

struct Mino {
    int x, y;
};

using Shape = std::array<Mino, 4>;

class Tetromino {
public:
    enum class Type { I, O, T, S, Z, J, L, None };

    Tetromino(Type type = Type::None); // constructeur

    // Position sur la grille
    int x = 0;
    int y = 0;

    Type type() const { return m_type; }
    int rotation() const { return m_rotation; }

    // Retourne les 4 blocs dans la rotation actuelle (coords relatives)
    Shape blocks() const;

    // Retourne les 4 blocs en coords absolues (x+this->x, y+this->y)
    Shape absoluteBlocks() const;

    // Rotations
    void rotateRight();
    void rotateLeft();

    // Couleur associée à chaque type
    static QColor colorOf(Type type);
    QColor color() const { return colorOf(m_type); }

    // Génère une pièce aléatoire
    static Tetromino random();

private:
    Type m_type;
    int  m_rotation; // 0=spawn, 1=R, 2=180, 3=L

    // Table de toutes les formes : [type][rotation][bloc]
    static const Shape s_shapes[7][4];
};

#endif // TETROMINO_H