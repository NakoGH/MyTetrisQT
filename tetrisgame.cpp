#include "tetrisgame.h"

// Points par nombre de lignes effacées (Tetris Guideline)
static const int LINE_POINTS[5] = { 0, 100, 300, 500, 800 };

TetrisGame::TetrisGame(QObject* parent)
    : QObject(parent)
    , m_board(this)
    , m_current(Tetromino::Type::None)
    , m_next(Tetromino::random())
    , m_hold(Tetromino::Type::None)
    , m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &TetrisGame::tick);
    connect(&m_board, &TetrisBoard::boardChanged, this, &TetrisGame::boardChanged);
}

void TetrisGame::start()
{
    m_board.reset();
    m_score    = 0;
    m_level    = 1;
    m_lines    = 0;
    m_holdUsed = false;
    m_gameOver = false;
    m_hold     = Tetromino(Tetromino::Type::None);
    m_next     = Tetromino::random();

    emit scoreChanged();
    emit levelChanged();
    emit linesChanged();
    emit gameOverChanged();
    emit holdChanged();
    emit nextChanged();

    spawnNext();

    m_running = true;
    emit runningChanged();
    updateTimerInterval();
    m_timer->start();
}

void TetrisGame::pause()
{
    if (!m_running) return;
    m_running = !m_running;
    m_running ? m_timer->start() : m_timer->stop();
    emit runningChanged();
}

// tick — descend la pièce d'une ligne à chaque intervalle
void TetrisGame::tick()
{
    Tetromino moved = m_current;
    ++moved.y;

    if (m_board.canPlace(moved)) {
        m_current = moved;
        emit boardChanged();
    } else {
        lockAndSpawn();
    }
}

// Mouvements du joueur
void TetrisGame::moveLeft()
{
    if (!m_running || m_gameOver) return;
    tryMove(-1, 0);
}

void TetrisGame::moveRight()
{
    if (!m_running || m_gameOver) return;
    tryMove(1, 0);
}

void TetrisGame::softDrop()
{
    if (!m_running || m_gameOver) return;
    Tetromino moved = m_current;
    ++moved.y;
    if (m_board.canPlace(moved)) {
        m_current = moved;
        m_score += 1; // bonus soft drop
        emit scoreChanged();
        emit boardChanged();
    } else {
        lockAndSpawn();
    }
}

void TetrisGame::hardDrop()
{
    if (!m_running || m_gameOver) return;

    int ghostRow = m_board.ghostY(m_current);
    int dropped  = ghostRow - m_current.y;
    m_current.y  = ghostRow;
    m_score += dropped * 2; // bonus hard drop
    emit scoreChanged();

    lockAndSpawn();
}

void TetrisGame::rotate()
{
    if (!m_running || m_gameOver) return;

    Tetromino rotated = m_current;
    rotated.rotateRight();

    // Wall kick basique : essaie ±1, ±2 en X si bloqué
    const int kicks[] = { 0, -1, 1, -2, 2 };
    for (int kick : kicks) {
        rotated.x = m_current.x + kick;
        if (m_board.canPlace(rotated)) {
            m_current = rotated;
            emit boardChanged();
            return;
        }
    }
}

// Hold
void TetrisGame::holdPiece()
{
    if (!m_running || m_gameOver || m_holdUsed) return;

    m_holdUsed = true;

    if (m_hold.type() == Tetromino::Type::None) {
        // Première utilisation : envoyer la pièce en hold, spawner la next
        m_hold = Tetromino(m_current.type());
        spawnNext();
    } else {
        // Échanger current ↔ hold
        Tetromino::Type savedType = m_hold.type();
        m_hold    = Tetromino(m_current.type());
        m_current = Tetromino(savedType);
        m_current.x = 3;
        m_current.y = 0;
    }

    emit holdChanged();
    emit boardChanged();
}

// genere la next pièce
void TetrisGame::spawnNext()
{
    m_current      = m_next;
    m_current.x    = 3;
    m_current.y    = 0;
    m_next         = Tetromino::random();
    m_holdUsed     = false;

    emit nextChanged();

    if (!m_board.canPlace(m_current)) {
        // Impossible de spawner → game over
        m_gameOver = true;
        m_running  = false;
        m_timer->stop();
        emit gameOverChanged();
        emit runningChanged();
    }
}

//fige la pièce, efface les lignes, spawne la suivante
void TetrisGame::lockAndSpawn()
{
    m_board.lockPiece(m_current);

    int cleared = m_board.clearLines();
    if (cleared > 0) {
        addScore(cleared);
        emit lineClearEffect(cleared);
    }

    spawnNext();
}

void TetrisGame::tryMove(int dx, int dy)
{
    Tetromino moved = m_current;
    moved.x += dx;
    moved.y += dy;
    if (m_board.canPlace(moved)) {
        m_current = moved;
        emit boardChanged();
    }
}

// système de points (cf le wiki Tetris Guideline )
void TetrisGame::addScore(int cleared)
{
    m_score += LINE_POINTS[cleared] * m_level;
    m_lines += cleared;

    // Niveau : +1 tous les 10 lignes
    int newLevel = m_lines / 10 + 1;
    if (newLevel != m_level) {
        m_level = newLevel;
        updateTimerInterval();
        emit levelChanged();
    }

    emit scoreChanged();
    emit linesChanged();
}

void TetrisGame::updateTimerInterval()
{
    // cf Guidelines : niveau 1 = 800ms, niveau 20 = ~33ms
    int ms = qMax(33, 800 - (m_level - 1) * 40);
    m_timer->setInterval(ms);
}

QVariantList TetrisGame::cells() const
{
    QVariantList list = m_board.cells(); // copie de la grille figée

    // Superpose la pièce courante
    for (const auto& b : m_current.absoluteBlocks()) {
        int idx = b.y * TetrisBoard::COLS + b.x;
        if (idx >= 0 && idx < list.size())
            list[idx] = m_current.color().name();
    }
    return list;
}

// ghost : grille avec seulement la ghost piece
QVariantList TetrisGame::ghost() const
{
    QVariantList list(TetrisBoard::ROWS * TetrisBoard::COLS, QString(""));

    int gy = m_board.ghostY(m_current);
    Tetromino g = m_current;
    g.y = gy;

    for (const auto& b : g.absoluteBlocks()) {
        int idx = b.y * TetrisBoard::COLS + b.x;
        if (idx >= 0 && idx < list.size())
            list[idx] = QString("#444444"); // couleur ghost
    }
    return list;
}

// holdCells / nextCells : grille 4×4 pour affichage dans les panneaux
QVariantList TetrisGame::holdCells() const
{
    return pieceToGrid(m_hold, 4, 4);
}

QVariantList TetrisGame::nextCells() const
{
    return pieceToGrid(m_next, 4, 4);
}

QVariantList TetrisGame::pieceToGrid(const Tetromino& t,
                                     int gridRows, int gridCols) const
{
    QVariantList list(gridRows * gridCols, QString(""));
    if (t.type() == Tetromino::Type::None) return list;

    for (const auto& b : t.blocks()) {
        int idx = b.y * gridCols + b.x;
        if (idx >= 0 && idx < list.size())
            list[idx] = t.color().name();
    }
    return list;
}