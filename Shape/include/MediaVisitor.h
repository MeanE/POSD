#ifndef MEDIAVISITOR_H
#define MEDIAVISITOR_H

class ShapeMedia;
class ComboMedia;
class TextMedia;

class MediaVisitor
{
public:
    virtual void visitShapeMedia(ShapeMedia* shapeMedia) =0;
    virtual void visitComboMedia(ComboMedia* comboMedia) =0;
    virtual void visitTextMedia(TextMedia* textMedia) =0;
};

#endif // MEDIAVISITOR_H
