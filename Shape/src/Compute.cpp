#include "Compute.h"
#include <algorithm>
using namespace std;

double Compute::sumOfPerimeter (const vector<Shape*> &shp) const{
    double sum(0);
    for(Shape* sp: shp){
        sum+=sp->perimeter();
    }
    return sum;
}

double Compute::sumOfArea (const vector<Shape*> &shp) const{
    double sum(0);
    for(Shape* sp: shp){
        sum+=sp->area();
    }
    return sum;
}

Shape* Compute::maxArea(vector<Shape*> &shp) const{
    return *max_element(shp.begin(),shp.end(),
                        [](Shape* &a, Shape* &b){ //compare with area
                            return a->area() < b->area();
                        });
}

void Compute::sortByDecreasingPerimeter(vector<Shape*> &shp){
    sort(shp.begin(),shp.end(),
         [](Shape* &a, Shape* &b){//compare with perimeter
            return a->perimeter() > b->perimeter();
         });
}
