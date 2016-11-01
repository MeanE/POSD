#include "ComboMediaBuilder.h"

ComboMediaBuilder::ComboMediaBuilder():_comboMedia(0){}

void ComboMediaBuilder::buildComboMedia(){
    _comboMedia=new ComboMedia();
}

void ComboMediaBuilder::buildShapeMedia(Shape* s){
//    throw string("ComboMediaBuilder CAN'T Build ShapeMedia!!!");
    if(!_comboMedia)
        throw string("Should Call buildComboMedia() first!!!");
    _comboMedia->add(new ShapeMedia(s));
}

Media* ComboMediaBuilder::getMedia(){return _comboMedia;}

void ComboMediaBuilder::addMedia(Media* media){
    _comboMedia->add(media);
}
