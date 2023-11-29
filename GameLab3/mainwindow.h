#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include "GameController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void handleCommand();
    void resetGame();

private:
    Ui::MainWindow *ui;
    GameController *gameController;
};

#endif // MAINWINDOW_H
