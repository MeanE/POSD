#ifndef MEDIAVISITOR_H
#define MEDIAVISITOR_H

class ShapeMedia;
class ComboMedia;

class MediaVisitor
{
public:
    virtual void visitShapeMedia(ShapeMedia* shapeMedia) =0;
    virtual void visitComboMedia(ComboMedia* comboMedia) =0;
};

#endif // MEDIAVISITOR_H
