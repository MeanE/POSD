#include "AreaVisitor.h"

AreaVisitor::AreaVisitor():_area(0.){}

double AreaVisitor::getArea() const{return _area;}

void AreaVisitor::visitShapeMedia(ShapeMedia* shapeMedia){
    _area += shapeMedia->area();
}

void AreaVisitor::visitComboMedia(ComboMedia* comboMedia){
    _area += 0.;
}

void AreaVisitor::visitTextMedia(TextMedia* textMedia){
    _area += textMedia->getText()->getBoundingBox()->area();
}
