#ifndef MEDIA_H
#define MEDIA_H

class MediaVisitor;

class Media
{
public:
    virtual void accept(MediaVisitor* mv) =0;
};

#endif // MEDIA_H
