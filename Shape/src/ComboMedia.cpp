#include "ComboMedia.h"
#include <sstream>

vector<Media*> ComboMedia::getMediaPieces() const{return _mediaPieces;}

void ComboMedia::add(Media* mediaPieces){_mediaPieces.push_back(mediaPieces);}

void ComboMedia::accept(MediaVisitor* mediaVisitor){
    for(Media *m: _mediaPieces)
        m->accept(mediaVisitor);
    mediaVisitor->visitComboMedia(this);
}

string ComboMedia::description() const{
    stringstream ss;
    ss<< "combo(";

    for(Media *m: _mediaPieces)
        ss<< m->description();

    ss<< ")";
    return ss.str();
}

