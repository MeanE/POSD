#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle(double leftTopX, double leftTopY, double length, double width, string name):
        _x(leftTopX), _y(leftTopY), _length(length), _width(width){_name=name;}

double Rectangle::area() const{return _length*_width;}
double Rectangle::perimeter() const{return 2*(_length+_width);}
