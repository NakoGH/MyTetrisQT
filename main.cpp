#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "tetrisgame.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<TetrisGame>("Tetris", 1, 0, "TetrisGame");

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("MyTetrisQT", "App");

    return app.exec();
}
