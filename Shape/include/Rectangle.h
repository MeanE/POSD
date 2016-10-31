#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(double, double, double, double, std::string name="unknown");

    double area() const;
    double perimeter() const;
    string description() const;

private:
    double _x, _y, _length, _width;
};

#endif // RECTANGLE_H
