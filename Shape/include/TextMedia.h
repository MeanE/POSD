#ifndef TEXTMEDIA_H
#define TEXTMEDIA_H

#include "Text.h"
#include "Media.h"
#include "MediaVisitor.h"

class TextMedia : public Media
{
public:
    TextMedia(Text* text);
    Text* getText() const;

    void accept(MediaVisitor* mv) ;
    string description() const;

private:
    Text* _text;
};

#endif // TEXTMEDIA_H
