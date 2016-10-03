#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle(double, double, double, double, double, double);

    bool getIsTriangle() const;

    double area() const;
    double perimeter() const;
    void isTriangle();

private:
    double ax,ay,bx,by,cx,cy;
    bool isTriangleChecked=false, trueTriangle;
};

#endif // TRIANGLE_H
