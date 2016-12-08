#ifndef COMBOMEDIABUILDER_H
#define COMBOMEDIABUILDER_H

#include "MediaBuilder.h"
#include "ComboMedia.h"

class ComboMediaBuilder : public MediaBuilder
{
public:
    ComboMediaBuilder();
    void buildComboMedia();
    void buildComboMedia(string name);
    void buildShapeMedia(Shape* s);
    Media *getMedia();
    void addMedia(Media* media);

private:
    ComboMedia* _comboMedia;
};

#endif // COMBOMEDIABUILDER_H
