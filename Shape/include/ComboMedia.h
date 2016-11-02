#ifndef COMBOMEDIA_H
#define COMBOMEDIA_H

#include "Media.h"
#include <vector>
#include "MediaVisitor.h"
#include "DescriptionVisitor.h"
#include <string>
using namespace std;

class ComboMedia : public Media
{
public:
    vector<Media*> getMediaPieces() const;

    void add(Media* mediaPieces);
    void accept(MediaVisitor* mediaVisitor);
    string description() const;
    void removeMedia(Media* m);

private:
    vector<Media*> _mediaPieces;
};

#endif // COMBOMEDIA_H

