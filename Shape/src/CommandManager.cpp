#include "CommandManager.h"

CommandManager::CommandManager(){}

void CommandManager::executeCMD(Command *cmd){
    undocmds.push(cmd);
    cmd->execute();
}

void CommandManager::undoCMD(){
    if(!undocmds.empty()){
        redocmds.push(undocmds.top());
        undocmds.top()->undo();
        undocmds.pop();
    }
}

void CommandManager::redoCMD(){
    if(!redocmds.empty()){
        undocmds.push(redocmds.top());
        redocmds.top()->redo();
        redocmds.pop();
    }
}

