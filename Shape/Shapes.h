#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

double PI=3.1415926;

class Shape{
public:
    virtual double area() const =0;
    virtual double perimeter() const =0;
};

class Circle : public Shape{
public:
    Circle(double centerX, double centerY, double radius):
        cx(centerX), cy(centerY), r(radius){}
    double area() const {return PI*r*r;}
    double perimeter() const {return PI*2*r;}
private:
    double cx,cy,r;
};

class Rectangle : public Shape{
public:
    Rectangle(double leftTopX, double leftTopY, double length, double width):
        x(leftTopX), y(leftTopY), l(length), w(width){}
    double area() const {return l*w;}
    double perimeter() const {return 2*(l+w);}
private:
    double x,y,l,w;
};

#endif // SHAPES_H_INCLUDED
