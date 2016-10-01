#include "Rectangle.h"

Rectangle::Rectangle(double leftTopX, double leftTopY, double length, double width):
        x(leftTopX),y(leftTopY),l(length),w(width){}

double Rectangle::area() const{return l*w;}
double Rectangle::perimeter() const{return 2*(l+w);}
