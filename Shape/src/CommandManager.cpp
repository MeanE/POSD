#include "CommandManager.h"

CommandManager::CommandManager(){}

void CommandManager::ExecuteCMD(Command *cmd){
    undocmds.push(cmd);
    cmd->Execute();
}

void CommandManager::UndoCMD(){
    if(!undocmds.empty()){
        redocmds.push(undocmds.top());
        undocmds.top()->Undo();
        undocmds.pop();
    }
}

void CommandManager::RedoCMD(){
    if(!redocmds.empty()){
        undocmds.push(redocmds.top());
        redocmds.top()->Redo();
        redocmds.pop();
    }
}

