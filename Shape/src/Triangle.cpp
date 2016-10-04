#include "Triangle.h"
#include <cmath>
using namespace std;

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3, string name):
        _ax(x1), _ay(y1), _bx(x2), _by(y2), _cx(x3), _cy(y3){
            isTriangle();
            _name=name;
}

bool Triangle::getIsTriangle() const{return _trueTriangle;}

/** Heron's formula
  * use three point to compute area
  *        1 |ax bx cx ax|
  * area = - |           |
  *        2 |ay by cy ay| */
double Triangle::area() const{
    return abs((_ax*_by+ _bx*_cy+ _cx*_ay)-(_ay*_bx+ _by*_cx+ _cy*_ax))/2;
}

double Triangle::perimeter() const{
    double abLength=sqrt(pow(_ax-_bx, 2) + pow(_ay-_by, 2));
    double acLength=sqrt(pow(_ax-_cx, 2) + pow(_ay-_cy, 2));
    double bcLength=sqrt(pow(_bx-_cx, 2) + pow(_by-_cy, 2));

    return abLength+ acLength+ bcLength;
}

void Triangle::isTriangle(){
    if(!_isTriangleChecked){
        double abLength=sqrt(pow(_ax-_bx, 2) + pow(_ay-_by, 2));
        double acLength=sqrt(pow(_ax-_cx, 2) + pow(_ay-_cy, 2));
        double bcLength=sqrt(pow(_bx-_cx, 2) + pow(_by-_cy, 2));

        _trueTriangle=(abLength+acLength > bcLength) &&
                      (abLength+bcLength > acLength) &&
                      (acLength+bcLength > abLength);

        _isTriangleChecked=true;
    }
}

