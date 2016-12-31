#ifndef DEFINECOMMAND_H
#define DEFINECOMMAND_H

#include "Command.h"
#include "Media.h"
#include <string>
#include <map>
using namespace std;

class DefineCommand : public Command
{
public:
    DefineCommand(string content, map<string, Media*>* medias);
    ~DefineCommand(){}
    void Execute();
    void Undo();
    void Redo();

private:
    string _content;
    map<string, Media*>* _medias;
};

#endif // DEFINECOMMAND_H
