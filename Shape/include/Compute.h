#ifndef COMPUTE_H
#define COMPUTE_H

#include "Shape.h"
#include <vector>

class Compute
{
public:
    double sumOfPerimeter (std::vector<Shape*> &) const;
    Shape* maxArea(std::vector<Shape*> &) const;
};

#endif // COMPUTE_H
