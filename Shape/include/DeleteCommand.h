#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "Command.h"


class DeleteCommand : public Command
{
public:
    DeleteCommand();
    ~DeleteCommand();
    void Execute();
    void Undo();
    void Redo();

private:
};

#endif // DELETECOMMAND_H
