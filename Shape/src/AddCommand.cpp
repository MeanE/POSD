#include "AddCommand.h"

#include "Medias.h"
#include "Visitors.h"
#include <vector>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <algorithm>


AddCommand::AddCommand(string content, map<string, Media*>* medias):_content(content), _medias(medias){}

vector<string> getTokens(string content, string spliter);
bool isDigits(const string &str);

void AddCommand::execute(){
    vector<string> tokens=getTokens(_content, "=,() {}");
    if(tokens.size()<1) return;

    if(tokens.size()==3){
        if(tokens[1]=="to"){
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
            else if(tokens[0]==tokens[2]){
                cout<<"Can not add itself.\n";
                return;
            }
            else{
                if(ComboMedia* cm=dynamic_cast<ComboMedia*>(comboMediaIt->second)){
                    /**copy */
                    for(auto it: *_medias){
                        if(ComboMedia* cm=dynamic_cast<ComboMedia*>(it.second)){
                            ComboMedia* tempCm = new ComboMedia(*cm);
                            //cout<<tempCm->name()<<endl;
                            string name=cm->name();
                            name=name.substr(0,name.find_first_of('{'));
                            //cout<<name<<endl;
                            _tempMedias[name]=tempCm;
                        }
                        if(ShapeMedia* sm=dynamic_cast<ShapeMedia*>(it.second)){
                            ShapeMedia* tempSm = new ShapeMedia(*sm);
                            //cout<<tempSm->name()<<endl;
                            string name=sm->name();
                            name=name.substr(0,name.find_first_of(' '));
                            //cout<<name<<endl;
                            _tempMedias[name]=tempSm;
                        }
                    }

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

void AddCommand::undo(){
    _medias->swap(_tempMedias);
    _tempMedias.clear();
}

void AddCommand::redo(){
//    for(auto it: *_medias)
//            cout<<"   "<<it.first<<endl;
//        /**media description output*/
//    for(auto it: *_medias){Media* m = it.second;DescriptionVisitor dv;m->accept(&dv);cout<<dv.getDescription()<<endl;}
    execute();
}
