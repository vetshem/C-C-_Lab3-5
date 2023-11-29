#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <QObject>
#include "GameController.h"

class CommandInterpreter : public QObject {
    Q_OBJECT

public:
    CommandInterpreter(GameController *controller, QObject *parent = nullptr);

public slots:
    void interpretCommand(const QString &command);

private:
    GameController *gameController;
};

#endif // COMMANDINTERPRETER_H
