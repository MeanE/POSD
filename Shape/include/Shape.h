#ifndef SHAPE_H
#define SHAPE_H

#include <string>
using namespace std;

class Shape
{
public:
    virtual double area() const =0;
    virtual double perimeter() const =0;
    virtual string description() const = 0;

    string getName() const;

protected:
    string _name;
};

#endif // SHAPE_H
