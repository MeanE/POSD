#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape
{
public:
    Circle(double, double, double);

    double area() const;
    double perimeter() const;

private:
    double cx,cy,r;
};

#endif // CIRCLE_H
