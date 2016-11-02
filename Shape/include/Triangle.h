#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle(double, double, double, double, double, double, std::string name="unknown");

    bool getIsTriangle() const;

    double area() const;
    double perimeter() const;
    string description() const;
    void isTriangle();

private:
    double _ax, _ay, _bx, _by, _cx, _cy;
    bool _isTriangleChecked=false, _trueTriangle;
};

#endif // TRIANGLE_H
