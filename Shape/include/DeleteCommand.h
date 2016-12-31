#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "Command.h"


class DeleteCommand : public Command
{
public:
    DeleteCommand();
    ~DeleteCommand();
    void execute();
    void undo();
    void redo();

private:
};

#endif // DELETECOMMAND_H
