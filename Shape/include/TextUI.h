#ifndef TEXTUI_H
#define TEXTUI_H

#include "Shapes.h"
#include "Medias.h"
#include "Visitors.h"
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
    map<string, Media*> medias;
};

#endif // TEXTUI_H
