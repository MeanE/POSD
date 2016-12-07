#ifndef TEXT_H
#define TEXT_H

#include "Rectangle.h"

class Text
{
public:
    Text(Rectangle* boundingBox, string text, string name="unknown");
    string getContent() const;
    Rectangle* getBoundingBox() const;
    string getName() const;
private:
    Rectangle* _boundingBox;
    string _content;
    string _name;
};

#endif // TEXT_H
