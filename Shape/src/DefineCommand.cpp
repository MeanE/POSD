#include "DefineCommand.h"

#include "Builders.h"
#include "Shapes.h"
#include <vector>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <algorithm>

DefineCommand::DefineCommand(string content, map<string, Media*>* medias):_content(content), _medias(medias){}

vector<string> getTokens(string content, string spliter);
bool isDigits(const string &str);

void DefineCommand::execute(){
//cout<<content<<endl;
    vector<string> tokens=getTokens(_content, "=,() {}");

    //cout<<tokens.size()<<endl; for(string token: tokens) cout<<token<<endl;
    if(tokens.size()<2) return;

    /**build Media*/
    bool isBuild = false;
    if(tokens[1]!="combo" && tokens.size()>3){
        /**check parameter is digit*/
        for(size_t i=2; i<tokens.size(); i++)
            if(!isDigits(tokens[i])) return;
        //cout<<"xxx"<<endl;
        /**build ShapeMedia*/
        ShapeMediaBuilder smb;
        if(tokens[1]=="Circle"){
            /**Circle has only 3 parameters*/
            if(tokens.size()-2 == 3){
                double param1=atof(tokens[2].c_str());
                double param2=atof(tokens[3].c_str());
                double param3=atof(tokens[4].c_str());
                Circle* cir=new Circle(param1,param2,param3,tokens[0]);
                smb.buildShapeMedia(cir);
                isBuild=true;
            }
            else{
                cout<<"Input illegal (Circle has only 3 parameters).\n";
                return;
            }
        }
        else if(tokens[1]=="Rectangle"){
            /**Rectangle has only 4 parameters*/
            if(tokens.size()-2 == 4){
                double param1=atof(tokens[2].c_str());
                double param2=atof(tokens[3].c_str());
                double param3=atof(tokens[4].c_str());
                double param4=atof(tokens[5].c_str());
                Rectangle* rect=new Rectangle(param1,param2,param3,param4,tokens[0]);
                smb.buildShapeMedia(rect);
                isBuild=true;
            }
            else{
                cout<<"Input illegal (Rectangle has only 4 parameters).\n";
                return;
            }
        }
        else if(tokens[1]=="Triangle"){
            /**Triangle has only 6 parameters*/
            if(tokens.size()-2 == 6){
                double param1=atof(tokens[2].c_str());
                double param2=atof(tokens[3].c_str());
                double param3=atof(tokens[4].c_str());
                double param4=atof(tokens[5].c_str());
                double param5=atof(tokens[6].c_str());
                double param6=atof(tokens[7].c_str());
                Triangle* tri=new Triangle(param1,param2,param3,param4,param5,param6,tokens[0]);
                smb.buildShapeMedia(tri);
                isBuild=true;
            }
            else{
                cout<<"Input illegal (Triangle has only 6 parameters).\n";
                return;
            }
        }

        /**find key*/
        if(isBuild){
            if(_medias->find(tokens[0]) == _medias->end()){
                printf(">> %s (", tokens[1].c_str());
                for(size_t i=2; i<tokens.size(); i++){
                    if(i==2) cout<<tokens[i];
                    else cout<<","<<tokens[i];
                }
                cout<<")\n";
                (*_medias)[tokens[0]] = smb.getMedia();
            }
            else printf("%s already exists.\n", tokens[0].c_str());
        }
    }
    /**build ComboMedia*/
    else if(tokens[1]=="combo"){
        ComboMediaBuilder cmb;
        cmb.buildComboMedia(tokens[0]);
        /**at least 2 shapes to compose*/
        if(tokens.size()-2 >= 2){
            for(size_t i=2; i<tokens.size(); i++){
                if(_medias->find(tokens[i]) == _medias->end()){
                    cout<<tokens[i]<<" not found.\n";
                    return;
                }
                else{
                    Media* m = _medias->find(tokens[i])->second;
                    cmb.addMedia(m);
                    isBuild = true;
                }
            }
        }
        else{
            cout<<"At least 2 shapes to compose.\n";
            return;
        }

        /**find key*/
        if(isBuild){
            if(_medias->find(tokens[0]) == _medias->end() && isBuild)
                (*_medias)[tokens[0]] = cmb.getMedia();
            else printf("%s already exists.\n", tokens[0].c_str());
        }
    }
}

void DefineCommand::undo(){
    vector<string> tokens=getTokens(_content, "=,() {}");
    _medias->erase(tokens[0]);
}

void DefineCommand::redo(){
    execute();
}


