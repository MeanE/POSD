#ifndef PERIMETERVISITOR_H
#define PERIMETERVISITOR_H

#include "MediaVisitor.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"
#include "TextMedia.h"

class PerimeterVisitor : public MediaVisitor
{
public:
    PerimeterVisitor();
    double getPerimeter() const;

    void visitShapeMedia(ShapeMedia* shapeMedia);
    void visitComboMedia(ComboMedia* comboMedia);
    void visitTextMedia(TextMedia* textMedia);

private:
    double _perimeter;
};

#endif // PERIMETERVISITOR_H
