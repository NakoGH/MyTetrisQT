#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "tetrisboard.h"
#include "tetromino.h"
#include <QObject>
#include <QTimer>
#include <QtQml/qqmlregistration.h>

class TetrisGame : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QVariantList cells    READ cells    NOTIFY boardChanged)
    Q_PROPERTY(QVariantList ghost    READ ghost    NOTIFY boardChanged)
    Q_PROPERTY(QVariantList holdCells  READ holdCells  NOTIFY holdChanged)
    Q_PROPERTY(QVariantList nextCells  READ nextCells  NOTIFY nextChanged)
    Q_PROPERTY(int  score   READ score   NOTIFY scoreChanged)
    Q_PROPERTY(int  level   READ level   NOTIFY levelChanged)
    Q_PROPERTY(int  lines   READ lines   NOTIFY linesChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(bool gameOver READ gameOver NOTIFY gameOverChanged)

public:
    explicit TetrisGame(QObject* parent = nullptr);

    // ── Getters ───────────────────────────────────────────────────────────────
    QVariantList cells()     const;
    QVariantList ghost()     const;
    QVariantList holdCells() const;
    QVariantList nextCells() const;
    int  score()    const { return m_score; }
    int  level()    const { return m_level; }
    int  lines()    const { return m_lines; }
    bool running()  const { return m_running; }
    bool gameOver() const { return m_gameOver; }

public slots:
    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE void rotate();
    Q_INVOKABLE void softDrop();
    Q_INVOKABLE void hardDrop();
    Q_INVOKABLE void holdPiece();

signals:
    void boardChanged();
    void holdChanged();
    void nextChanged();
    void scoreChanged();
    void levelChanged();
    void linesChanged();
    void runningChanged();
    void gameOverChanged();
    void lineClearEffect(int count); // pour animations QML

private slots:
    void tick();

private:
    // ── État ──────────────────────────────────────────────────────────────────
    TetrisBoard   m_board;
    Tetromino     m_current;
    Tetromino     m_next;
    Tetromino     m_hold;
    bool          m_holdUsed  = false; // une seule fois par pièce
    bool          m_running   = false;
    bool          m_gameOver  = false;
    int           m_score     = 0;
    int           m_level     = 1;
    int           m_lines     = 0;
    QTimer*       m_timer;

    // ── Helpers ───────────────────────────────────────────────────────────────
    void spawnNext();
    void tryMove(int dx, int dy);
    void lockAndSpawn();
    void addScore(int clearedLines);
    void updateTimerInterval();
    QVariantList pieceToGrid(const Tetromino& t,
                             int gridRows, int gridCols) const;
};

#endif // TETRISGAME_H