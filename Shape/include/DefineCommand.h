#ifndef DEFINECOMMAND_H
#define DEFINECOMMAND_H

#include "Command.h"


class DefineCommand : public Command
{
public:
    DefineCommand();
    ~DefineCommand();
    void Execute();
    void Undo();
    void Redo();

private:

};

#endif // DEFINECOMMAND_H
