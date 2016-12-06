#ifndef TEXTUI_H
#define TEXTUI_H

#include "Shapes.h"
#include "Medias.h"
#include "Visitors.h"
using namespace std;

class TextUI
{
public:
    void run();

private:
    void analysisInstructions(string userInput);
};

#endif // TEXTUI_H
