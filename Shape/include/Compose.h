#ifndef COMPOSE_H
#define COMPOSE_H

#include "Shape.h"
#include <vector>

class Compose : public Shape
{
public:
    Compose(string name="unknown");

    double area() const;
    double perimeter() const;
    void add(Shape* shp);

private:
    vector<Shape*> _pieces;
};

#endif // COMPOSE_H

