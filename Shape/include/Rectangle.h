#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(double, double, double, double);

    double area() const;
    double perimeter() const;

private:
    double x,y,l,w;
};

#endif // RECTANGLE_H
