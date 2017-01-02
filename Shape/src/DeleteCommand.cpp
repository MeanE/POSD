#include "DeleteCommand.h"

#include "Medias.h"
#include "Visitors.h"
#include <vector>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <algorithm>

DeleteCommand::DeleteCommand(string content, map<string, Media*>* medias):_content(content), _medias(medias){}

vector<string> getTokens(string content, string spliter);
bool isDigits(const string &str);

void copyMap(DeleteCommand &dc){
    for(auto it: *dc._medias){
        if(ComboMedia* cm=dynamic_cast<ComboMedia*>(it.second)){
            ComboMedia* tempCm = new ComboMedia(*cm);
            //cout<<tempCm->name()<<endl;
            string name=cm->name();
            name=name.substr(0,name.find_first_of('{'));
            //cout<<name<<endl;
            dc._tempMedias[name]=tempCm;
        }
        if(ShapeMedia* sm=dynamic_cast<ShapeMedia*>(it.second)){
            ShapeMedia* tempSm = new ShapeMedia(*sm);
            //cout<<tempSm->name()<<endl;
            string name=sm->name();
            name=name.substr(0,name.find_first_of(' '));
            //cout<<name<<endl;
            dc._tempMedias[name]=tempSm;
        }
    }
}

void DeleteCommand::execute(){
    vector<string> tokens=getTokens(_content, "=,() {}");
    if(tokens.size()<1) return;

    if(tokens.size()==1){
        if(_medias->find(tokens[0]) == _medias->end())
            cout<<tokens[0]<<" does not exist.\n";
        else{
            auto targetIt =_medias->find(tokens[0]);
            for(auto it: *_medias){
                if(ComboMedia* cm=dynamic_cast<ComboMedia*>(it.second)){
                    copyMap(*this);
                    cm->removeMedia(targetIt->second);
                }
            }
            _medias->erase(targetIt);
        }

        return;
    }
    else if(tokens.size()==3){
        if(tokens[1]=="from"){
            auto firstMediaIt=_medias->find(tokens[0]);
            auto comboMediaIt=_medias->find(tokens[2]);

            if(firstMediaIt == _medias->end()){
                cout<<tokens[0]<<" does not exist.\n";
                return;
            }
            else if(comboMediaIt == _medias->end()){
                cout<<tokens[2]<<" does not exist.\n";
                return;
            }
            else{
                if(ComboMedia* cm=dynamic_cast<ComboMedia*>(comboMediaIt->second)){
                    copyMap(*this);
                    cm->removeMedia(firstMediaIt->second);
                }
                else{
                    cout<<"Should input a ComboMedia after \"from\".\n";
                    return;
                }
            }
        }
    }
}

void DeleteCommand::undo(){
    _medias->swap(_tempMedias);
    _tempMedias.clear();
}

void DeleteCommand::redo(){
    execute();
}
