#include "TextUI.h"
#include "Builders.h"
#include "Visitors.h"
#include "Shapes.h"
#include "Commands.h"
#include <sstream>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <stack>

string help(){
    ostringstream sout;
	sout << "This system provide some instructions for user.\n"
        << "For example:\n"
        << "\'def\' name = Shape(x,y,z,...) or name = combo{name,name}\n"
        << "\'name.area?\' or \'name.perimeter?\'\n"
        << "\'save\' name to \"File_Name.txt\" & \'load\' \"File_Name.txt\"\n"
        << "\'add\' name to name(combo) & \'show\'\n"
        << "\'delete\' name or name from name(combo)\n"
        << "\'Ctrl+Z\' to undo & \'Ctrl+Y\' to redo\n";

	return sout.str();
}
void TextUI::run(){
    cout<<help();
    while(1){
        cout<< ":- ";
        string userInput;
        getline(cin,userInput);
        //cout<<userInput<<endl;
        if(cin.eof()){ ///Ctrl+Z
            cout<<">> Ctrl+Z(Undo)\n";
            _commandManager.undoCMD();
        }
        analysisInstructions(userInput);
        cin.clear();

    }
}

void TextUI::analysisInstructions(string userInput){
    string asciiCtrlY; asciiCtrlY=(char)25;
    if(userInput == asciiCtrlY){
        cout<<">> Ctrl+Y(Redo)\n";
        _commandManager.redoCMD();
        return;
    }
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
    string content = userInput.substr(firstSpace+1, userInput.length()-1);

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
    else if(instruction == "load" && content.length()){
        instructionLoad(content);
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

    delete src;

    return tokens;
}
bool isDigits(const string &str){
    return str.find_first_not_of("-0123456789") == std::string::npos;
    //return all_of(str.begin(), str.end(), ::isdigit);
}
void TextUI::instructionDefine(string content){
    _commandManager.executeCMD(new DefineCommand(content, &_medias));
}

void TextUI::instructionShow() const{
    if(_medias.empty()) cout<<"There is nothing yet.\n";
    else{
        for(auto it: _medias)
            cout<<"   "<<it.first<<endl;
        /**media description output*/
        //for(auto it: _medias){Media* m = it.second;DescriptionVisitor dv;m->accept(&dv);cout<<dv.getDescription()<<endl;}
    }
}

void TextUI::instructionDelete(string content){
    _commandManager.executeCMD(new DeleteCommand(content, &_medias));
}

void TextUI::instructionAdd(string content){
    _commandManager.executeCMD(new AddCommand(content, &_medias));
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

void TextUI::instructionLoad(string content){
    //cout<<content<<endl;
    vector<string> tokens=getTokens(content, "\"");
    //cout<<tokens.size()<<endl; for(string token: tokens) cout<<token<<endl;
    if(tokens.size()!=1) return;

    string fileName=tokens[0];
    //cout<<fileName<<endl;
    size_t firstDot = fileName.find_first_of('.');
    if(firstDot == string::npos) return;
    string fileExtension = fileName.substr(firstDot+1, fileName.length()-1);
    if(fileExtension!="txt"){
        cout<<"Only accept .txt\n";
        return;
    }
    else{
        ifstream fin(fileName, ios::in);
        if(fin){
            cout<<">> loading "<<fileName<<" ...\n";
            if(!fin.eof()){
                string description;
                getline(fin,description);
                string name;
                getline(fin,name);
                vector<string> nameTokens=getTokens(name," {}");
                //cout<<nameTokens.size()<<endl; for(string token: nameTokens) cout<<token<<endl;

                /**clear map*/
                _medias.clear();
                /**build Media*/
                vector<string> descriptionTokens=getTokens(description,"()");
                //cout<<descriptionTokens.size()<<endl; for(string token: descriptionTokens) cout<<token<<endl;
                int descriptionCount=0;
                int comboCount=0;
                /**build ComboMedia*/
                if(descriptionTokens[0]=="combo"){
                    cout<<nameTokens[0]<<" = "<<name<<" = "<<description<<endl;
                    stack<MediaBuilder*> sMb;
                    ShapeMediaBuilder smb;
                    for(auto it=descriptionTokens.begin(); it!=descriptionTokens.end(); it++){
                        auto& token=*it;
                        //cout<<token<<endl;
                        if(token=="combo"){
                            //cout<<descriptionTokens[descriptionCount]<<endl;
                            sMb.push(new ComboMediaBuilder());
                            ((ComboMediaBuilder*)sMb.top())->buildComboMedia(nameTokens[descriptionCount]);
                            /**put Media in map*/
                            _medias[nameTokens[0]]=sMb.top()->getMedia();
                            descriptionCount++;
                            comboCount++;
                            continue;
                        }
                        else if(token=="r"){
                            auto& nextToken=*(it+1);
                            istringstream sout(nextToken);
                            //cout<<sout.str()<<endl;
                            double leftTopX, leftTopY, length, width;
                            sout>>leftTopX>>leftTopY>>length>>width;

                            Rectangle* rect=new Rectangle(leftTopX,leftTopY, length,width, nameTokens[descriptionCount]);
                            sMb.top()->buildShapeMedia(rect);
                            /**put Media in map*/
                            smb.buildShapeMedia(rect);
                            _medias[nameTokens[descriptionCount]]=smb.getMedia();
                            descriptionCount++;

                            continue;
                        }
                        else if(token=="c"){
                            auto& nextToken=*(it+1);
                            istringstream sout(nextToken);
                            //cout<<sout.str()<<endl;
                            double centerX, centerY, radius;
                            sout>>centerX>>centerY>>radius;

                            Circle* cir=new Circle(centerX,centerY, radius,nameTokens[descriptionCount]);
                            sMb.top()->buildShapeMedia(cir);
                            /**put Media in map*/
                            smb.buildShapeMedia(cir);
                            _medias[nameTokens[descriptionCount]]=smb.getMedia();
                            descriptionCount++;
                            continue;
                        }
                        else if(token=="t"){
                            auto& nextToken=*(it+1);
                            istringstream sout(nextToken);
                            //cout<<sout.str()<<endl;
                            double x1, y1, x2, y2, x3, y3;
                            sout>>x1>>y1>>x2>>y2>>x3>>y3;

                            Triangle* tri=new Triangle(x1, y1, x2, y2, x3, y3,nameTokens[descriptionCount]);
                            sMb.top()->buildShapeMedia(tri);
                            /**put Media in map*/
                            smb.buildShapeMedia(tri);
                            _medias[nameTokens[descriptionCount]]=smb.getMedia();
                            descriptionCount++;
                            continue;
                        }
                        else if(token.empty() && comboCount>1){ /**ComboMedia end*/
                            ComboMedia* cm=(ComboMedia*) sMb.top()->getMedia();
                            sMb.pop();
                            ((ComboMediaBuilder*)sMb.top())->addMedia(cm);
                            continue;
                        }
                    }
                }
                /**build shapeMedia*/
                else{
                    cout<<name<<" = "<<description<<endl;
                    ShapeMediaBuilder smb;
                    for(auto it=descriptionTokens.begin(); it!=descriptionTokens.end(); it++){
                        auto& token=*it;
                        //cout<<token<<endl;
                        if(token=="r"){
                            auto& nextToken=*(it+1);
                            istringstream sout(nextToken);
                            //cout<<sout.str()<<endl;
                            double leftTopX, leftTopY, length, width;
                            sout>>leftTopX>>leftTopY>>length>>width;

                            Rectangle* rect=new Rectangle(leftTopX,leftTopY, length,width, nameTokens[descriptionCount]);
                            /**put Media in map*/
                            smb.buildShapeMedia(rect);
                            _medias[name]=smb.getMedia();
                            continue;
                        }
                        if(token=="c"){
                            auto& nextToken=*(it+1);
                            istringstream sout(nextToken);
                            //cout<<sout.str()<<endl;
                            double centerX, centerY, radius;
                            sout>>centerX>>centerY>>radius;

                            Circle* cir=new Circle(centerX,centerY, radius,nameTokens[descriptionCount]);
                            /**put Media in map*/
                            smb.buildShapeMedia(cir);
                            _medias[name]=smb.getMedia();
                            continue;
                        }
                        if(token=="t"){
                            auto& nextToken=*(it+1);
                            istringstream sout(nextToken);
                            //cout<<sout.str()<<endl;
                            double x1, y1, x2, y2, x3, y3;
                            sout>>x1>>y1>>x2>>y2>>x3>>y3;

                            Triangle* tri=new Triangle(x1, y1, x2, y2, x3, y3,nameTokens[descriptionCount]);
                            /**put Media in map*/
                            smb.buildShapeMedia(tri);
                            _medias[name]=smb.getMedia();
                            continue;
                        }
                    }
                }
            }
        }
        else{
            cout<<fileName<<" dose not exist.\n";
            return;
        }

    }
}


