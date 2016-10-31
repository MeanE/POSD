#include "Rectangle.h"
#include <sstream>
using namespace std;

Rectangle::Rectangle(double leftTopX, double leftTopY, double length, double width, string name):
        _x(leftTopX), _y(leftTopY), _length(length), _width(width){_name=name;}

double Rectangle::area() const{return _length*_width;}
double Rectangle::perimeter() const{return 2*(_length+_width);}
string Rectangle::description() const {
    stringstream ss;
    ss << "r(" << _x << " " << _y << " " << _length << " " << _width << ") ";
    return ss.str();
}
