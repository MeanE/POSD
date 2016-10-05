#include "Compose.h"
#include "Compute.h"
using namespace std;

Compose::Compose(string name){_name=name;}

double Compose::area() const{
    Compute cmp;
    return cmp.sumOfArea(_pieces);
}

double Compose::perimeter() const{
    Compute cmp;
    return cmp.sumOfPerimeter(_pieces);
}

void Compose::add(Shape* shp){_pieces.push_back(shp);}
