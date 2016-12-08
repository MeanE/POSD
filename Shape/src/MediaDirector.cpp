#include "MediaDirector.h"
#include "ComboMediaBuilder.h"
#include "Shapes.h"
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>

void MediaDirector::setMediaBuilder(stack<MediaBuilder*>* mbs){
    _mb=mbs;
}

void MediaDirector::concrete(string content){
    /**from myShape.txt
      *combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))*/
    vector<string> tokens;

    char* src=new char[content.length()+1];
    strcpy(src, content.c_str());

    char* ptr=strtok(src, "()");
    while(ptr!=NULL) {
        string piece=string(ptr);
        piece.erase(0,piece.find_first_not_of(" ")); /**trim head space*/
        piece.erase(piece.find_last_not_of(" ") + 1);/**trim last space*/
        tokens.push_back(string(piece));
        ptr=strtok(NULL, "()");
    }

    int comboCount=0;

    for(auto it=tokens.begin(); it!=tokens.end(); it++){
        auto& token=*it;
        //cout<<token<<endl;
        if(token=="combo"){
            _mb->push(new ComboMediaBuilder());
            _mb->top()->buildComboMedia();
            comboCount++;
            continue;
        }
        if(token=="r"){
            auto& nextToken=*(it+1);
            istringstream sout(nextToken);
            //cout<<sout.str()<<endl;
            double leftTopX, leftTopY, length, width;
            sout>>leftTopX>>leftTopY>>length>>width;

            _mb->top()->buildShapeMedia(new Rectangle(leftTopX,leftTopY, length,width));
            continue;
        }
        if(token=="c"){
            auto& nextToken=*(it+1);
            istringstream sout(nextToken);
            //cout<<sout.str()<<endl;
            double centerX, centerY, radius;
            sout>>centerX>>centerY>>radius;

            _mb->top()->buildShapeMedia(new Circle(centerX,centerY, radius));
            continue;
        }
        if(token=="t"){
            auto& nextToken=*(it+1);
            istringstream sout(nextToken);
            //cout<<sout.str()<<endl;
            double x1, y1, x2, y2, x3, y3;
            sout>>x1>>y1>>x2>>y2>>x3>>y3;

            _mb->top()->buildShapeMedia(new Triangle(x1, y1, x2, y2, x3, y3));
            continue;
        }
        if(token.empty() && comboCount>1){ /**ComboMedia end*/
            ComboMedia* cm=(ComboMedia*) _mb->top()->getMedia();
            _mb->pop();
            ((ComboMediaBuilder*)_mb->top())->addMedia(cm);
            continue;
        }
    }

    delete []src;
}
