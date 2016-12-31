#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "Command.h"


class AddCommand : public Command
{
public:
    AddCommand();
    ~AddCommand();
    void Execute();
    void Undo();
    void Redo();

private:
};

#endif // ADDCOMMAND_H
