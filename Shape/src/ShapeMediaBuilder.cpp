#include "ShapeMediaBuilder.h"

ShapeMediaBuilder::ShapeMediaBuilder():_shapeMedia(0){}

void ShapeMediaBuilder::buildComboMedia(){
    throw string("ShapeMediaBuilder CAN'T Build ComboMedia!!!");
}

void ShapeMediaBuilder::buildShapeMedia(Shape* s){
    _shapeMedia=new ShapeMedia(s);
}

Media* ShapeMediaBuilder::getMedia(){return _shapeMedia;}
