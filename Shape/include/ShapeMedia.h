#ifndef SHAPEMEDIA_H
#define SHAPEMEDIA_H

#include "Media.h"
#include "Shape.h"
#include "MediaVisitor.h"

class ShapeMedia : public Media
{
public:
    ShapeMedia(Shape* shape);

    Shape* getShape() const;

    double area() const;
    double perimeter() const;
    void accept(MediaVisitor* mediaVisitor);
    string description() const;
    string name() const;

private:
    Shape* _shape;
};

#endif // SHAPEMEDIA_H
