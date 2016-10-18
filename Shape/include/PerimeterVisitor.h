#ifndef PERIMETERVISITOR_H
#define PERIMETERVISITOR_H

#include "MediaVisitor.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"

class PerimeterVisitor : public MediaVisitor
{
public:
    PerimeterVisitor();
    double getPerimeter() const;

    void visitShapeMedia(ShapeMedia* shapeMedia);
    void visitComboMedia(ComboMedia* comboMedia);

private:
    double _perimeter;
};

#endif // PERIMETERVISITOR_H
