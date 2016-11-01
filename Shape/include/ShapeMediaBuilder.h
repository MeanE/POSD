#ifndef SHAPEMEDIABUILDER_H
#define SHAPEMEDIABUILDER_H

#include "MediaBuilder.h"
#include "ShapeMedia.h"

class ShapeMediaBuilder : public MediaBuilder
{
public:
    ShapeMediaBuilder();
    void buildComboMedia();
    void buildShapeMedia(Shape * s);
    Media *getMedia();

private:
    ShapeMedia* _shapeMedia;
};

#endif // SHAPEMEDIABUILDER_H
