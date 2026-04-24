#include "tetrisboard.h"

TetrisBoard::TetrisBoard(QObject* parent)
    : QObject(parent)
{
    reset();
}

// ─────────────────────────────────────────────────────────────────────────────
// reset
// ─────────────────────────────────────────────────────────────────────────────
void TetrisBoard::reset()
{
    for (auto& row : m_grid)
        row.fill(0);
    emit boardChanged();
}

// ─────────────────────────────────────────────────────────────────────────────
// canPlace — vérifie si la pièce t tient dans la grille sans collision
// ─────────────────────────────────────────────────────────────────────────────
bool TetrisBoard::canPlace(const Tetromino& t) const
{
    for (const auto& b : t.absoluteBlocks()) {
        // Hors limites horizontales ou bas de grille
        if (b.x < 0 || b.x >= COLS || b.y >= ROWS)
            return false;
        // Hors limites haut (pièce qui spawn au-dessus) → autorisé
        if (b.y < 0)
            continue;
        // Cellule déjà occupée
        if (m_grid[b.y][b.x] != 0)
            return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// isGameOver — au moins un bloc verrouillé sur la ligne 0
// ─────────────────────────────────────────────────────────────────────────────
bool TetrisBoard::isGameOver() const
{
    for (int col = 0; col < COLS; ++col)
        if (m_grid[0][col] != 0)
            return true;
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// lockPiece — fige la pièce courante dans la grille
// ─────────────────────────────────────────────────────────────────────────────
void TetrisBoard::lockPiece(const Tetromino& t)
{
    int colorIdx = typeToIndex(t.type());
    for (const auto& b : t.absoluteBlocks()) {
        if (b.y >= 0 && b.y < ROWS && b.x >= 0 && b.x < COLS)
            m_grid[b.y][b.x] = colorIdx;
    }
    emit boardChanged();
}

// ─────────────────────────────────────────────────────────────────────────────
// clearLines — supprime les lignes complètes et fait descendre le reste
//              retourne le nombre de lignes effacées (0–4)
// ─────────────────────────────────────────────────────────────────────────────
int TetrisBoard::clearLines()
{
    int cleared = 0;

    for (int row = ROWS - 1; row >= 0; ) {
        // Ligne pleine ?
        bool full = true;
        for (int col = 0; col < COLS; ++col) {
            if (m_grid[row][col] == 0) { full = false; break; }
        }

        if (full) {
            // Faire descendre toutes les lignes au-dessus
            for (int r = row; r > 0; --r)
                m_grid[r] = m_grid[r - 1];
            m_grid[0].fill(0);
            ++cleared;
            // Ne pas décrémenter row : re-vérifier la même ligne
        } else {
            --row;
        }
    }

    if (cleared > 0)
        emit boardChanged();

    return cleared;
}

// ─────────────────────────────────────────────────────────────────────────────
// ghostY — calcule jusqu'où tomberait la pièce (pour afficher le fantôme)
// ─────────────────────────────────────────────────────────────────────────────
int TetrisBoard::ghostY(const Tetromino& t) const
{
    Tetromino ghost = t;
    while (canPlace(ghost)) {
        ++ghost.y;
    }
    // On est allé un cran trop loin
    return ghost.y - 1;
}

// ─────────────────────────────────────────────────────────────────────────────
// cells — expose la grille à QML sous forme de liste de couleurs (QString)
// ─────────────────────────────────────────────────────────────────────────────
QVariantList TetrisBoard::cells() const
{
    QVariantList list;
    list.reserve(ROWS * COLS);
    for (const auto& row : m_grid)
        for (int val : row)
            list.append(val == 0 ? QString("") : indexToColor(val).name());
    return list;
}

// ─────────────────────────────────────────────────────────────────────────────
// Helpers
// ─────────────────────────────────────────────────────────────────────────────
int TetrisBoard::typeToIndex(Tetromino::Type t)
{
    return static_cast<int>(t) + 1; // 1–7, 0 réservé à "vide"
}

QColor TetrisBoard::indexToColor(int idx)
{
    if (idx < 1 || idx > 7) return Qt::black;
    return Tetromino::colorOf(static_cast<Tetromino::Type>(idx - 1));
}