#ifndef AREAVISITOR_H
#define AREAVISITOR_H

#include "MediaVisitor.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"
#include "TextMedia.h"

class AreaVisitor : public MediaVisitor
{
public:
    AreaVisitor();
    double getArea() const;

    void visitShapeMedia(ShapeMedia* shapeMedia);
    void visitComboMedia(ComboMedia* comboMedia);
    void visitTextMedia(TextMedia* textMedia);

private:
    double _area;
};

#endif // AREAVISITOR_H
