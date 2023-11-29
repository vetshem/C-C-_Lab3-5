// GameWidget.cpp
#include "GameWidget.h"

GameWidget::GameWidget(QWidget *parent) : QTextEdit(parent) {}

void GameWidget::updateGameText(const QString &text) {
    append(text);
}

void GameWidget::updateGameState(const QString &state) {
    appendGameState(state);
}

void GameWidget::appendGameState(const QString &state) {
    QString gameText = toPlainText();
    gameText += "\n";  // Додаємо новий рядок
    gameText += state;
    setPlainText(gameText);
}
