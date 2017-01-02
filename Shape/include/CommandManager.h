#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "Command.h"
#include <stack>
using namespace std;

class CommandManager
{
public:
    void executeCMD(Command *cmd);
    void undoCMD();
    void redoCMD();

private:
    stack<Command*> undocmds;
    stack<Command*> redocmds;
};


#endif // COMMANDMANAGER_H

