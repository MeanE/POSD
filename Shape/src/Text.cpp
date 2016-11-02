#include "Text.h"

Text::Text(Rectangle* boundingBox, string text):_boundingBox(boundingBox), _content(text){}
string Text::getContent() const{return _content;}
Rectangle* Text::getBoundingBox() const{return _boundingBox;}
