#ifndef MYDOCUMENT_H
#define MYDOCUMENT_H

#include "Document.h"
#include <fstream>

class MyDocument : public Document
{
public:
    ~MyDocument();
protected :
    void openFile(const string name);
    bool canOpenDocument(const string name);
    string readFile();
private:
    fstream _myFile;
};

#endif // MYDOCUMENT_H
