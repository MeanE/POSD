#ifndef TEXTUI_H
#define TEXTUI_H

#include "Medias.h"
#include "CommandManager.h"
#include <map>
using namespace std;

class TextUI
{
public:
    void run();

private:
    void analysisInstructions(string userInput);
    void instructionDefine(string content);
    void instructionShow() const;
    void instructionDelete(string content);
    void instructionAdd(string content);
    void instructionNameDotAction(string name, string action);
    void instructionSave(string content);
    void instructionLoad(string content);

    map<string, Media*> _medias;
    CommandManager _commandManager;
};

#endif // TEXTUI_H
