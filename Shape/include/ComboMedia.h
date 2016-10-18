#ifndef COMBOMEDIA_H
#define COMBOMEDIA_H

#include "Media.h"
#include <vector>
#include "MediaVisitor.h"
using namespace std;

class ComboMedia : public Media
{
public:
    vector<Media*> getMediaPieces() const;

    void add(Media* mediaPieces);
    void accept(MediaVisitor* mediaVisitor);

private:
    vector<Media*> _mediaPieces;
};

#endif // COMBOMEDIA_H
