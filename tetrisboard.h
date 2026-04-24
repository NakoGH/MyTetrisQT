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

    // ── Queries ──────────────────────────────────────────────────────────────
    bool canPlace(const Tetromino& t) const;
    bool isGameOver() const;

    // ── Mutations ────────────────────────────────────────────────────────────
    void lockPiece(const Tetromino& t);   // fige la pièce sur la grille
    int  clearLines();                    // supprime lignes pleines, retourne le compte
    void reset();                         // remet la grille à zéro

    // ── QML interface ────────────────────────────────────────────────────────
    // Liste de ROWS*COLS couleurs (QString) — "" = vide
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