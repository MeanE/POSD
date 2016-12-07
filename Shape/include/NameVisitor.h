#ifndef NAMEVISITOR_H
#define NAMEVISITOR_H

#include <string>
#include "MediaVisitor.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"
#include "TextMedia.h"

class NameVisitor : public MediaVisitor
{
public:
    NameVisitor();
    string getName() const;

    void visitShapeMedia(ShapeMedia* shapeMedia);
    void visitComboMedia(ComboMedia* comboMedia);
    void visitTextMedia(TextMedia* textMedia);

private:
    string _name;
};

#endif // NAMEVISITOR_H
