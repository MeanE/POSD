#ifndef COMPUTE_H
#define COMPUTE_H

#include "Shape.h"
#include <vector>

class Compute
{
public:
    double sumOfPerimeter (const vector<Shape*> &shp) const;
    double sumOfArea (const vector<Shape*> &shp) const;
    Shape* maxArea(vector<Shape*> &shp) const;
    void sortByDecreasingPerimeter(vector<Shape*> &shp);
};

#endif // COMPUTE_H
