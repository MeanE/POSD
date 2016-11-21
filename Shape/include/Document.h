#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
using namespace std;

class Document
{
public :
    virtual ~Document(){};

    string openDocument(const string name){
        if(!canOpenDocument(name))
            throw std::string("file is not existed.");
        openFile(name);
        return readFile();
    }
protected :
    virtual void openFile(const string name) = 0;
    virtual bool canOpenDocument(const string name) = 0;
    virtual string readFile() = 0;
};


#endif // DOCUMENT_H
