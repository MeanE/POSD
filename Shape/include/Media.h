#ifndef MEDIA_H
#define MEDIA_H

#include <string>
using namespace std;

class MediaVisitor;

class Media
{
public:
    virtual void accept(MediaVisitor* mv) =0;
    virtual string description() const=0;
    virtual string name() const=0;
};

#endif // MEDIA_H
