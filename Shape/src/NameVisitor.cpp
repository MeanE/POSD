#include "NameVisitor.h"

NameVisitor::NameVisitor():_name(""){}

string NameVisitor::getName() const{return _name;}

void NameVisitor::visitShapeMedia(ShapeMedia* shapeMedia){
    _name += shapeMedia->name();
}
void NameVisitor::visitComboMedia(ComboMedia* comboMedia){
    _name = comboMedia->name();
}
void NameVisitor::visitTextMedia(TextMedia* textMedia){
    _name += textMedia->name();
}
