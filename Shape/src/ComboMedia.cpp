#include "ComboMedia.h"
#include <sstream>
#include <stack>
#include <iostream>

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

void ComboMedia::removeMedia(Media* m){
    for(Media *mp: _mediaPieces){
        /**dynamic_cast<Type*>
          *same as instanceof in JAVA
          *if not the same class
          *then return a NULL class*/
        if(ComboMedia* cm=dynamic_cast<ComboMedia*>(mp))
            cm->removeMedia(m);
        else{
            string target = m->description();
            for(size_t i=0; i<_mediaPieces.size(); i++){
                string compare = _mediaPieces[i]->description();
                if(compare==target)
                    _mediaPieces.erase(_mediaPieces.begin()+i);
            }
        }
    }
}


