#include "PerimeterVisitor.h"

PerimeterVisitor::PerimeterVisitor():_perimeter(0.){}

double PerimeterVisitor::getPerimeter() const{return _perimeter;}

void PerimeterVisitor::visitShapeMedia(ShapeMedia* shapeMedia){
    _perimeter += shapeMedia->perimeter();
}

void PerimeterVisitor::visitComboMedia(ComboMedia* comboMedia){
    _perimeter += 0.;
}
