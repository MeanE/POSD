#ifndef DESCRIPTIONVISITOR_H
#define DESCRIPTIONVISITOR_H

#include <string>
#include "MediaVisitor.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"

class DescriptionVisitor : public MediaVisitor
{
public:
    DescriptionVisitor();
    string getDescription() const;

    void visitShapeMedia(ShapeMedia* shapeMedia);
    void visitComboMedia(ComboMedia* comboMedia){};
private:
    string _description;
};

#endif // DESCRIPTIONVISITOR_H
