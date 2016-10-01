#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle(double, double, double, double, double, double);

    double area() const;
    double perimeter() const;

private:
    double ax,ay,bx,by,cx,cy;
};

#endif // TRIANGLE_H
