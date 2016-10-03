#include "Compute.h"
using namespace std;

double Compute::sumOfPerimeter (vector<Shape*> &shp) const{
    double sum(0);
    for(Shape* &sp: shp){
        sum+=sp->area();
    }
    return sum;
}
