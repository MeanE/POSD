#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "Command.h"
#include <stack>
using namespace std;

class CommandManager
{
public:
    CommandManager();
    void ExecuteCMD(Command *cmd);
    void UndoCMD();
    void RedoCMD();

private:
    stack<Command*> undocmds;
    stack<Command*> redocmds;
};


#endif // COMMANDMANAGER_H

