#include "TextUI.h"
#include <sstream>
#include <iostream>
#include <cstring>
#include "Builders.h"
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include "Visitors.h"
#include "Shapes.h"
#include <fstream>

string help(){
    ostringstream sout;
	sout << "This system provide some instructions for user.\n"
        << "For example:\n"
        << "\'def\' name = Shape(x,y,z,...) or name = combo{name,name}\n"
        << "\'name.area?\' or \'name.perimeter?\'\n"
        << "\'save\' name to \"File_Name.txt\" & \'load\' \"File_Name.txt\"\n"
        << "\'add\' name to name(combo) & \'show\'\n"
        << "\'delete\' name or name from name(combo)\n";

	return sout.str();
}
void TextUI::run(){
    cout<<help();
    while(1){
        cout<< ":- ";
        string userInput;
        getline(cin,userInput);
        //cout<<input<<endl;
        analysisInstructions(userInput);
    }
}

void TextUI::analysisInstructions(string userInput){
    if(userInput == "show"){
        instructionShow();
        return;
    }

    size_t firstSpace = userInput.find_first_of(' ');
    /**name.action(e.g. area/perimeter)*/
    size_t firstDot = userInput.find_first_of('.');
    if(firstDot != string::npos && firstSpace == string::npos){
        string name = userInput.substr(0, firstDot);
        string action = userInput.substr(firstDot+1, userInput.length()-1);
        if(_medias.find(name)!=_medias.end()){
            instructionNameDotAction(name, action);
        }
        else{
            cout<<name<<" does not exist.\n";
            return;
        }
    }

    if(firstSpace == string::npos) return;
    string instruction = userInput.substr(0, firstSpace);
    string content = userInput.substr(firstSpace, userInput.length()-1);

    if(instruction == "def" && content.length()){
        instructionDefine(content);
        return;
    }
    else if(instruction == "delete" && content.length()){
        instructionDelete(content);
        return;
    }
    else if(instruction == "add" && content.length()){
        instructionAdd(content);
        return;
    }
    else if(instruction == "save" && content.length()){
        instructionSave(content);
        return;
    }
}

vector<string> getTokens(string content, string spliter){
    vector<string> tokens;

    char* src=new char[content.length()+1];
    strcpy(src, content.c_str());

    char* ptr=strtok(src, spliter.c_str());
    while(ptr!=NULL) {
        string piece=string(ptr);
        piece.erase(0,piece.find_first_not_of(" ")); /**trim head space*/
        piece.erase(piece.find_last_not_of(" ") + 1);/**trim last space*/
        tokens.push_back(string(piece));
        ptr=strtok(NULL, spliter.c_str());
    }

    return tokens;
}
bool isDigits(const string &str){
    return str.find_first_not_of("-0123456789") == std::string::npos;
    //return all_of(str.begin(), str.end(), ::isdigit);
}
void TextUI::instructionDefine(string content){
    //cout<<content<<endl;
    vector<string> tokens=getTokens(content, "=,() {}");

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
            if(_medias.find(tokens[0]) == _medias.end()){
                printf(">> %s (", tokens[1].c_str());
                for(size_t i=2; i<tokens.size(); i++){
                    if(i==2) cout<<tokens[i];
                    else cout<<","<<tokens[i];
                }
                cout<<")\n";
                _medias[tokens[0]] = smb.getMedia();
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
                if(_medias.find(tokens[i]) == _medias.end()){
                    cout<<tokens[i]<<" not found.\n";
                    return;
                }
                else{
                    Media* m = _medias.find(tokens[i])->second;
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
            if(_medias.find(tokens[0]) == _medias.end() && isBuild)
                _medias[tokens[0]] = cmb.getMedia();
            else printf("%s already exists.\n", tokens[0].c_str());
        }
    }
}

void TextUI::instructionShow() const{
    if(_medias.empty()) cout<<"There is nothing yet.\n";
    else{
        for(auto it: _medias)
            cout<<"   "<<it.first<<endl;
        /**media description output*/
        for(auto it: _medias){Media* m = it.second;DescriptionVisitor dv;m->accept(&dv);cout<<dv.getDescription()<<endl;}
    }
}

void TextUI::instructionDelete(string content){
    vector<string> tokens=getTokens(content, "=,() {}");
    if(tokens.size()<1) return;

    if(tokens.size()==1){
        if(_medias.find(tokens[0]) == _medias.end())
            cout<<tokens[0]<<" does not exist.\n";
        else{
            auto targetIt =_medias.find(tokens[0]);
            for(auto it: _medias){
                if(ComboMedia* cm=dynamic_cast<ComboMedia*>(it.second))
                    cm->removeMedia(targetIt->second);
            }
            _medias.erase(targetIt);
        }

        return;
    }
    else if(tokens.size()==3){
        if(tokens[1]=="from"){
            auto firstMediaIt=_medias.find(tokens[0]);
            auto comboMediaIt=_medias.find(tokens[2]);

            if(firstMediaIt == _medias.end()){
                cout<<tokens[0]<<" does not exist.\n";
                return;
            }
            else if(comboMediaIt == _medias.end()){
                cout<<tokens[2]<<" does not exist.\n";
                return;
            }
            else{
                if(ComboMedia* cm=dynamic_cast<ComboMedia*>(comboMediaIt->second))
                    cm->removeMedia(firstMediaIt->second);
                else{
                    cout<<"Should input a ComboMedia after \"from\".\n";
                    return;
                }
            }
        }
    }
}

void TextUI::instructionAdd(string content){
    vector<string> tokens=getTokens(content, "=,() {}");
    if(tokens.size()<1) return;

    if(tokens.size()==3){
        if(tokens[1]=="to"){
            auto firstMediaIt=_medias.find(tokens[0]);
            auto comboMediaIt=_medias.find(tokens[2]);

            if(firstMediaIt == _medias.end()){
                cout<<tokens[0]<<" does not exist.\n";
                return;
            }
            else if(comboMediaIt == _medias.end()){
                cout<<tokens[2]<<" does not exist.\n";
                return;
            }
            else if(tokens[0]==tokens[2]){
                cout<<"Can not add itself.\n";
                return;
            }
            else{
                if(ComboMedia* cm=dynamic_cast<ComboMedia*>(comboMediaIt->second)){
                    cm->add(firstMediaIt->second);

                    cout<<">> "<<tokens[2]<<" = ";
                    NameVisitor nv;
                    comboMediaIt->second->accept(&nv);
                    DescriptionVisitor dv;
                    comboMediaIt->second->accept(&dv);
                    cout<<nv.getName()<<"= "<<dv.getDescription()<<endl;
                }
                else{
                    cout<<"Should input a ComboMedia after \"to\".\n";
                    return;
                }
            }
        }
    }
}

void TextUI::instructionNameDotAction(string name, string action){
    //cout<<name<<" "<<action<<endl;
    if(action == "area?"){
        AreaVisitor av;
        _medias[name]->accept(&av);
        printf(">> %f\n", av.getArea());
    }
    else if(action == "perimeter?"){
        PerimeterVisitor pv;
        _medias[name]->accept(&pv);
        printf(">> %f\n", pv.getPerimeter());
    }
    else{
        printf("%s not %s's action.\n", action.c_str(), name.c_str());
    }
}

void TextUI::instructionSave(string content){
    vector<string> tokens=getTokens(content, "=,() \"{}");
    //cout<<tokens[0]<<endl<<endl<<endl;
    if(tokens.size()<1) return;

    if(tokens.size()==3){
        if(tokens[1]=="to"){
            auto mediaIt=_medias.find(tokens[0]);
            string fileName=tokens[2];

            size_t firstDot = fileName.find_first_of('.');
            if(firstDot == string::npos) return;
            string fileExtension = fileName.substr(firstDot+1, fileName.length()-1);

            if(mediaIt == _medias.end()){
                cout<<tokens[0]<<" does not exist.\n";
                return;
            }
            else if(fileExtension!="txt"){
                cout<<"Only accept .txt\n";
                return;
            }
            else{
                ofstream fout(fileName, ios::trunc);
                /**check file exist*/
                if(fout){
                    DescriptionVisitor dv;
                    mediaIt->second->accept(&dv);
                    NameVisitor nv;
                    mediaIt->second->accept(&nv);
                    fout<<dv.getDescription()<<endl<<nv.getName()<<endl;

                    printf(">> %s saved to %s\n", tokens[0].c_str(), fileName.c_str());
                }
            }
        }
    }
}


