#include "MyDocument.h"
MyDocument::~MyDocument(){_myFile.close();}

void MyDocument::openFile(const string name){
    if(!_myFile.is_open())
        _myFile.open(name, ios::in);
}

bool MyDocument::canOpenDocument(const string name){
    ifstream myFile(name.c_str());
    return myFile.good();
}

string MyDocument::readFile(){
    string content;
    if(!_myFile.eof())
        getline(_myFile,content);
    //_myFile.seekp(content.length());
    return content;
}
