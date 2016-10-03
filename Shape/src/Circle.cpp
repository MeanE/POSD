#include "Circle.h"
using namespace std;

const double PI=3.1415926;

Circle::Circle(double centerX, double centerY, double radius, string name):
        _cx(centerX), _cy(centerY), _radius(radius) {_name=name;}

double Circle::area() const{return PI*_radius*_radius;}
double Circle::perimeter() const{return PI*2*_radius;}
