#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "Command.h"
#include "Media.h"
#include <string>
#include <map>
using namespace std;

class AddCommand : public Command
{
public:
    AddCommand(string content, map<string, Media*>* medias);
    ~AddCommand(){}
    void execute();
    void undo();
    void redo();

private:
    string _content;
    map<string, Media*>* _medias;
    map<string, Media*> _tempMedias;
};

#endif // ADDCOMMAND_H
