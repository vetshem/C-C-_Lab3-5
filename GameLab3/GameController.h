#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTextEdit>

class GameController : public QObject {
    Q_OBJECT

public:
    GameController(QTextEdit *gameWidget, QObject *parent = nullptr);
    void resetGame();

public slots:
    void processCommand(const QString &command);


signals:
    void gameStateChanged(const QString &newState);
    void gameEnded(const QString &message);

private:
    QTextEdit *gameWidget;
    int movesLeft;
    int score;

    void updateGame();

};

#endif // GAMECONTROLLER_H
