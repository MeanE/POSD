#ifndef MEDIADIRECTOR_H
#define MEDIADIRECTOR_H

#include <stack>
#include <string>
#include "MediaBuilder.h"
using namespace std;

class MediaDirector
{
public :
    void setMediaBuilder(stack<MediaBuilder*>* mbs);
    void concrete(string content);
private :
    stack<MediaBuilder*>* _mb;

};

#endif // MEDIADIRECTOR_H
