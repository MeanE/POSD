#include "ComboMedia.h"

vector<Media*> ComboMedia::getMediaPieces() const{return _mediaPieces;}

void ComboMedia::add(Media* mediaPieces){_mediaPieces.push_back(mediaPieces);}

void ComboMedia::accept(MediaVisitor* mediaVisitor){
    for(Media *m: _mediaPieces)
        m->accept(mediaVisitor);
    mediaVisitor->visitComboMedia(this);
}



