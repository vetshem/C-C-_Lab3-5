#include "mainwindow.h"
#include <QAction>
#include <QToolBar>
#include "ui_mainwindow.h"
#include "GameController.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    gameController = new GameController(ui->gameText, this);

    QToolBar *toolBar = findChild<QToolBar*>("toolBar");
    QAction *submitAction = new QAction("Виконати дію", this);
    connect(submitAction, &QAction::triggered, this, &MainWindow::handleCommand);
    toolBar->addAction(submitAction);
    connect(gameController, &GameController::gameStateChanged, ui->gameText, &QTextEdit::append);
    QPushButton *resetButton = findChild<QPushButton*>("resetButton");
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);
}

void MainWindow::resetGame() {
    ui->gameText->clear();
    ui->commandLineEdit->clear();
    gameController->resetGame(); // Add a resetGame method in GameController to reset game state
}

void MainWindow::handleCommand() {
    QString command = ui->commandLineEdit->text();
    gameController->processCommand(command);
    ui->commandLineEdit->clear();
}
