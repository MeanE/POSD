#include "DescriptionVisitor.h"

DescriptionVisitor::DescriptionVisitor():_description(""){};

string DescriptionVisitor::getDescription() const{return _description;}

void DescriptionVisitor::visitShapeMedia(ShapeMedia* shapeMedia){
    _description += shapeMedia->getShape()->description();
}
