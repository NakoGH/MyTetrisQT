#ifndef TETRISBOARD_H
#define TETRISBOARD_H

#include "tetromino.h"
#include <QObject>
#include <QVariantList>
#include <array>

    class TetrisBoard : public QObject
{
    Q_OBJECT

public:
    static constexpr int COLS = 10;
    static constexpr int ROWS = 20;

    TetrisBoard(QObject* parent = nullptr);

    bool canPlace(const Tetromino& t) const;
    bool isGameOver() const;

    void lockPiece(const Tetromino& t);
    int  clearLines();
    void reset();

    // Liste de ROWS*COLS couleurs (QString)
    QVariantList cells() const;

    // Renvoie la ligne de drop (ghost piece)
    int ghostY(const Tetromino& t) const;

signals:
    void boardChanged();

private:
    // Grille interne : 0 = vide, sinon index de couleur (1–7)
    std::array<std::array<int, COLS>, ROWS> m_grid;

    static QColor indexToColor(int idx);
    static int    typeToIndex(Tetromino::Type t);
};

#endif // TETRISBOARD_H