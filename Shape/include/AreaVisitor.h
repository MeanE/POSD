#ifndef AREAVISITOR_H
#define AREAVISITOR_H

#include "MediaVisitor.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"

class AreaVisitor : public MediaVisitor
{
public:
    AreaVisitor();
    double getArea() const;

    void visitShapeMedia(ShapeMedia* shapeMedia);
    void visitComboMedia(ComboMedia* comboMedia);

private:
    double _area;
};

#endif // AREAVISITOR_H
