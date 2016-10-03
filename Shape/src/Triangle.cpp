#include "Triangle.h"
#include <cmath>
using namespace std;

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3):
        ax(x1),ay(y1),bx(x2),by(y2),cx(x3),cy(y3){isTriangle();}

bool Triangle::getIsTriangle() const{return trueTriangle;}

/** Triangle
  * Heron's formula
  * use three point to compute area
  *        1 |ax bx cx ax|
  * area = - |           |
  *        2 |ay by cy ay| */
double Triangle::area() const{
    return abs((ax*by+ bx*cy+ cx*ay)-(ay*bx+ by*cx+ cy*ax))/2;
}

double Triangle::perimeter() const{
    double abLength=sqrt(pow(ax-bx,2) + pow(ay-by,2));
    double acLength=sqrt(pow(ax-cx,2) + pow(ay-cy,2));
    double bcLength=sqrt(pow(bx-cx,2) + pow(by-cy,2));

    return abLength+ acLength+ bcLength;
}

void Triangle::isTriangle(){
    if(!isTriangleChecked){
        double abSlope=(ay-by) / (ax-bx);
        double acSlope=(ay-cy) / (ax-cx);
        double bcSlope=(by-cy) / (bx-cx);

        trueTriangle=(abSlope!=acSlope) && (abSlope!=bcSlope) && (acSlope!=bcSlope);

        isTriangleChecked=true;
    }
}
