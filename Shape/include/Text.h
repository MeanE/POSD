#ifndef TEXT_H
#define TEXT_H

#include "Rectangle.h"

class Text
{
public:
    Text(Rectangle* boundingBox, string text);
    string getContent() const;
    Rectangle* getBoundingBox() const;
private:
    Rectangle* _boundingBox;
    string _content;
};

#endif // TEXT_H
