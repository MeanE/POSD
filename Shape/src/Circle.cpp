#include "Circle.h"

const double PI=3.1415926;

Circle::Circle(double centerX, double centerY, double radius):
        cx(centerX),cy(centerY),r(radius){}

double Circle::area() const{return PI*r*r;}
double Circle::perimeter() const{return PI*2*r;}
