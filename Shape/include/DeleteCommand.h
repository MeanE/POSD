#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "Command.h"
#include "Media.h"
#include <string>
#include <map>

class DeleteCommand : public Command
{
    friend void copyMap(DeleteCommand &dc);
public:
    DeleteCommand(string content, map<string, Media*>* medias);
    ~DeleteCommand(){}
    void execute();
    void undo();
    void redo();

private:
    string _content;
    map<string, Media*>* _medias;
    map<string, Media*> _tempMedias;
};

#endif // DELETECOMMAND_H
