#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape
{
public:
    Circle(double, double, double, std::string name="unknown");

    double area() const;
    double perimeter() const;

private:
    double _cx, _cy, _radius;
};

#endif // CIRCLE_H
