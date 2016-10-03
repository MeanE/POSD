#include "Compute.h"
#include <algorithm>
using namespace std;

double Compute::sumOfPerimeter (vector<Shape*> &shp) const{
    double sum(0);
    for(Shape* &sp: shp){
        sum+=sp->perimeter();
    }
    return sum;
}

bool myMaxCompareOfShapeArea(Shape* &a, Shape* &b){return a->area() < b->area();}
Shape* Compute::maxArea(std::vector<Shape*> &shp) const{
    return *max_element(shp.begin(),shp.end(), myMaxCompareOfShapeArea);
}
