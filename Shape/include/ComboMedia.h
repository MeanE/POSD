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
    ComboMedia(string name="unknown"):_name(name){}

    vector<Media*> getMediaPieces() const;

    void add(Media* mediaPieces);
    void accept(MediaVisitor* mediaVisitor);
    string description() const;
    void removeMedia(Media* m);
    string name() const;

private:
    vector<Media*> _mediaPieces;
    string _name;
};

#endif // COMBOMEDIA_H

