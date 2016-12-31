#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "Command.h"


class AddCommand : public Command
{
public:
    AddCommand();
    ~AddCommand();
    void execute();
    void undo();
    void redo();

private:
};

#endif // ADDCOMMAND_H
