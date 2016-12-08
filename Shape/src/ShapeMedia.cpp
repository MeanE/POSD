#include "ShapeMedia.h"

ShapeMedia::ShapeMedia(Shape* shape):_shape(shape){}
Shape* ShapeMedia::getShape() const{return _shape;}

double ShapeMedia::area() const{return _shape->area();}
double ShapeMedia::perimeter() const{return _shape->perimeter();}

void ShapeMedia::accept(MediaVisitor* mediaVisitor){mediaVisitor->visitShapeMedia(this);}

string ShapeMedia::description() const{return _shape->description();}

string ShapeMedia::name() const{return _shape->getName();}
