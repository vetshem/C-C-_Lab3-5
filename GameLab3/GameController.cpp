#include "GameController.h"
#include <QRandomGenerator>

GameController::GameController(QTextEdit *gameWidget, QObject *parent)
    : QObject(parent), gameWidget(gameWidget), movesLeft(10), score(0) {}

void GameController::processCommand(const QString &command) {
    if (command == "повернути ліворуч") {
        score += QRandomGenerator::global()->bounded(0, 2); // Генерує випадкове значення від 1 до 4
        --movesLeft;
        emit gameStateChanged("Ви пішли ліворуч.");
        updateGame();
    } else if (command == "повернути праворуч") {
        score += QRandomGenerator::global()->bounded(-1, 6);
        --movesLeft;
        emit gameStateChanged("Ви пішли праворуч.");
        updateGame();
    } else if (command == "йти прямо") {
        score += QRandomGenerator::global()->bounded(-1, 2);
        --movesLeft;
        emit gameStateChanged("Ви пішли прямо.");
        updateGame();
    } else if(command == "help"||command=="допомога"){
        emit gameStateChanged("Доступні команди:\nповернути ліворуч\nповернути праворуч\nйти прямо");

    } else {
        --movesLeft;
        emit gameStateChanged("Невірний хід. Ви втратили 1 хід.");
        updateGame();
    }

    if (score >= 10) {
        emit gameEnded("Тут тіпа мав бути сигнал про завершення, але трохи лінь реалізувати!");
        emit gameStateChanged("Ви вийшли з лабіринту. Гра завершена!");
        movesLeft = 10;
        score = 10;
        updateGame();
    } else if (movesLeft <= 0){
        emit gameStateChanged("О ні! Ви заблукали =((");
        movesLeft = 0;
        score = 0;
        updateGame();
    }
}
void GameController::resetGame() {
    movesLeft = 10;
    score = 0;
    updateGame();
}


void GameController::updateGame() {
    QString gameText = gameWidget->toPlainText();
    gameText += "\n";  // Додаємо новий рядок
    gameText += QString("Moves Left: %1, Score: %2").arg(movesLeft).arg(score);
    gameWidget->setPlainText(gameText);
}
