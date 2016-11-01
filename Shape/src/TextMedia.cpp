#include "TextMedia.h"
#include <sstream>

TextMedia::TextMedia(Text* text):_text(text){}
Text* TextMedia::getText() const{return _text;}

void TextMedia::accept(MediaVisitor* mv){
    mv->visitTextMedia(this);
}

string TextMedia::description() const{
    stringstream ss;
    ss<<"text("
        <<_text->getBoundingBox()->description()
        <<"content("<<_text->getContent()<<")"
        <<") ";
    return ss.str();
}

