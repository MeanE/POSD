#include "Text.h"

Text::Text(Rectangle* boundingBox, string text, string name):_boundingBox(boundingBox), _content(text), _name(name){}
string Text::getContent() const{return _content;}
Rectangle* Text::getBoundingBox() const{return _boundingBox;}
string Text::getName() const{return _name;}
