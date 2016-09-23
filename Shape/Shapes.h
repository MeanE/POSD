#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <cmath>
#include <vector>
using namespace std;

double PI=3.1415926;

class Shape{
public:
    virtual double area() const =0;
    virtual double perimeter() const =0;
};

class Circle : public Shape{
public:
    Circle(double centerX, double centerY, double radius):
        cx(centerX),cy(centerY),r(radius){}

    double area() const{return PI*r*r;}
    double perimeter() const{return PI*2*r;}

private:
    double cx,cy,r;
};

class Rectangle : public Shape{
public:
    Rectangle(double leftTopX, double leftTopY, double length, double width):
        x(leftTopX),y(leftTopY),l(length),w(width){}

    double area() const{return l*w;}
    double perimeter() const{return 2*(l+w);}

private:
    double x,y,l,w;
};

class Triangle : public Shape{
public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3):
        ax(x1),ay(y1),bx(x2),by(y2),cx(x3),cy(y3){}

    /** Triangle
      * Heron's formula
      * use three point to compute area
      *       1 |ax bx cx ax|
      *area = - |           |
      *       2 |ay by cy ay| */
    double area() const{
        return abs((ax*by+ bx*cy+ cx*ay)-(ay*bx+ by*cx+ cy*ax))/2;
    }

    double perimeter() const{
        double abLength=sqrt(pow(ax-bx,2) + pow(ay-by,2));
        double acLength=sqrt(pow(ax-cx,2) + pow(ay-cy,2));
        double bcLength=sqrt(pow(bx-cx,2) + pow(by-cy,2));

        return abLength+ acLength+ bcLength;
    }

private:
    double ax,ay,bx,by,cx,cy;
};

double sumOfPerimeter (vector<Shape*> shp){
    double sum=0;
    for(Shape* sp: shp){
        sum+=sp->area();
    }
    return sum;
}
#endif // SHAPES_H_INCLUDED
