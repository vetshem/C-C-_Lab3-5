// GameWidget.h
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QTextEdit>

class GameWidget : public QTextEdit {
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);

public slots:
    void updateGameText(const QString &text);
    void updateGameState(const QString &state);

private:
    void appendGameState(const QString &state);  // Допоміжна функція для оновлення стану гри
};

#endif // GAMEWIDGET_H
