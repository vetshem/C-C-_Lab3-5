#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter(GameController *controller, QObject *parent)
    : QObject(parent), gameController(controller) {}

void CommandInterpreter::interpretCommand(const QString &command) {
    gameController->processCommand(command);
}
