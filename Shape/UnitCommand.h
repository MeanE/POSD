#ifndef UNITCOMMAND_H_INCLUDED
#define UNITCOMMAND_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "Medias.h"
#include "Visitors.h"
#include "Builders.h"
#include "Commands.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;

const double EPSLION_IN_UNITCOMMAND=0.000001;

TEST (Execute, DefineCommand) {
    cout<<"TestDefineCommand_Execute---------------\n";
    /**def cSmall = Circle(2,1,1)*/
    /**def rTall = Rectangle(1,10,2,8)*/
    /**def tBig = Triangle(1,22,34,-4,15,16)*/
    /**def comboExclamation = combo{rTall,cSmall}*/
    string content[] = {
        "cSmall = Circle(2,1,1)",
        "rTall = Rectangle(1,10,2,8)",
        "tBig = Triangle(1,-1, 4,-1, 4,3)",
        "comboExclamation = combo{rTall,cSmall,tBig}"
    };

    map<string, Media*> medias;
    for(int i=0; i<4; i++){
        DefineCommand defineCommand(content[i], &medias);
        defineCommand.execute();
    }

    /**STL map default use ascending sort by key*/
    string description[]={
        "c(2 1 1) ",
        "combo(r(1 10 2 8) c(2 1 1) t(1 -1 4 -1 4 3) )",
        "r(1 10 2 8) ",
        "t(1 -1 4 -1 4 3) "
    };

    int i=0;
    for(auto it: medias){
        Media* m = it.second;
        DescriptionVisitor dv;
        m->accept(&dv);
        //cout<<dv.getDescription()<<endl;
        CHECK(description[i++] == dv.getDescription());
    }
}

TEST (Undo, DefineCommand) {
    cout<<"TestDefineCommand_Undo---------------\n";
    /**def cSmall = Circle(2,1,1)*/
    /**def rTall = Rectangle(1,10,2,8)*/
    string content[] = {
        "cSmall = Circle(2,1,1)",
        "rTall = Rectangle(1,10,2,8)"
    };

    map<string, Media*> medias;
    DefineCommand dc1(content[0], &medias);
    dc1.execute();
    DefineCommand dc2(content[1], &medias);
    dc2.execute();
    dc2.undo();

    /**STL map default use ascending sort by key*/
    string description[]={
        "c(2 1 1) ",
        "r(1 10 2 8) "
    };

    stringstream ss;
    ss<<medias.size();
    string mediasSize = ss.str();
    auto it=medias.begin();
    DescriptionVisitor dv;
    it->second->accept(&dv);

    CHECK(("1" + description[0]) == (mediasSize + dv.getDescription()));
}

TEST (Redo, DefineCommand) {
    cout<<"TestDefineCommand_Redo---------------\n";
    /**def cSmall = Circle(2,1,1)*/
    /**def rTall = Rectangle(1,10,2,8)*/
    string content[] = {
        "cSmall = Circle(2,1,1)",
        "rTall = Rectangle(1,10,2,8)"
    };

    map<string, Media*> medias;
    DefineCommand dc1(content[0], &medias);
    dc1.execute();
    DefineCommand dc2(content[1], &medias);
    dc2.execute();
    dc2.undo();
    dc2.redo();

    /**STL map default use ascending sort by key*/
    string description[]={
        "c(2 1 1) ",
        "r(1 10 2 8) "
    };

    int i=0;
    for(auto it: medias){
        Media* m = it.second;
        DescriptionVisitor dv;
        m->accept(&dv);
        cout<<dv.getDescription()<<endl;
        CHECK(description[i++] == dv.getDescription());
    }
}

TEST (Execute, AddCommand) {
    cout<<"TestAddCommand_Execute---------------\n";
    /**c(2 1 1)
     * c(3 2 1)
     * combo(c(2 1 1) )
     * combo(c(3 2 1) )*/
    map<string, Media*> medias;
    Circle cir1(2,1,1,"cSmall");
    Circle cir2(3,2,1,"cMale");
    ShapeMediaBuilder smb;
    smb.buildShapeMedia(&cir1);
    medias["cSmall"]=smb.getMedia();
    smb.buildShapeMedia(&cir2);
    medias["cMale"]=smb.getMedia();
    ComboMediaBuilder cmb;
    cmb.buildComboMedia("comboExclamation");
    cmb.buildShapeMedia(&cir1);
    medias["comboExclamation"]=cmb.getMedia();
    cmb.buildComboMedia("combo2");
    cmb.buildShapeMedia(&cir2);
    medias["combo2"]=cmb.getMedia();

    /**add cMale to comboExclamation*/
    /**add combo2 to comboExclamation*/
    string content[]={
        "cMale to comboExclamation",
        "combo2 to comboExclamation"
    };
    AddCommand ac1(content[0], &medias);
    ac1.execute();
    AddCommand ac2(content[1], &medias);
    ac2.execute();

    /**STL map default use ascending sort by key*/
    string description[]={
        "c(3 2 1) ",
        "c(2 1 1) ",
        "combo(c(3 2 1) )",
        "combo(c(2 1 1) c(3 2 1) combo(c(3 2 1) ))"
    };

    //cout<<medias.size()<<endl;
    int i=0;
    for(auto it: medias){
        Media* m = it.second;
        DescriptionVisitor dv;
        m->accept(&dv);
        //cout<<dv.getDescription()<<endl;
        CHECK(description[i++] == dv.getDescription());
    }
}

TEST (Undo, AddCommand) {
    cout<<"TestAddCommand_Undo---------------\n";
    /**c(2 1 1)
     * c(3 2 1)
     * combo(c(2 1 1) )
     * combo(c(3 2 1) )*/
    map<string, Media*> medias;
    Circle cir1(2,1,1,"cSmall");
    Circle cir2(3,2,1,"cMale");
    ShapeMediaBuilder smb;
    smb.buildShapeMedia(&cir1);
    medias["cSmall"]=smb.getMedia();
    smb.buildShapeMedia(&cir2);
    medias["cMale"]=smb.getMedia();
    ComboMediaBuilder cmb;
    cmb.buildComboMedia("comboExclamation");
    cmb.buildShapeMedia(&cir1);
    medias["comboExclamation"]=cmb.getMedia();
    cmb.buildComboMedia("combo2");
    cmb.buildShapeMedia(&cir2);
    medias["combo2"]=cmb.getMedia();

    /**add cMale to comboExclamation*/
    /**add combo2 to comboExclamation*/
    string content[]={
        "cMale to comboExclamation"
    };
    AddCommand ac1(content[0], &medias);
    ac1.execute();
    ac1.undo();

    /**STL map default use ascending sort by key*/
    string description[]={
        "c(3 2 1) ",
        "c(2 1 1) ",
        "combo(c(3 2 1) )",
        "combo(c(2 1 1) )"
    };

    int i=0;
    for(auto it: medias){
        Media* m = it.second;
        DescriptionVisitor dv;
        m->accept(&dv);
        //cout<<dv.getDescription()<<endl;
        CHECK(description[i++] == dv.getDescription());
    }
}

TEST (Redo, AddCommand) {
    cout<<"TestAddCommand_Redo---------------\n";
    /**c(2 1 1)
     * c(3 2 1)
     * combo(c(2 1 1) )
     * combo(c(3 2 1) )*/
    map<string, Media*> medias;
    Circle cir1(2,1,1,"cSmall");
    Circle cir2(3,2,1,"cMale");
    ShapeMediaBuilder smb;
    smb.buildShapeMedia(&cir1);
    medias["cSmall"]=smb.getMedia();
    smb.buildShapeMedia(&cir2);
    medias["cMale"]=smb.getMedia();
    ComboMediaBuilder cmb;
    cmb.buildComboMedia("comboExclamation");
    cmb.buildShapeMedia(&cir1);
    medias["comboExclamation"]=cmb.getMedia();
    cmb.buildComboMedia("combo2");
    cmb.buildShapeMedia(&cir2);
    medias["combo2"]=cmb.getMedia();

    /**add cMale to comboExclamation*/
    string content[]={
        "cMale to comboExclamation"
    };
    AddCommand ac1(content[0], &medias);
    ac1.execute();
    ac1.undo();
    ac1.redo();

    /**STL map default use ascending sort by key*/
    string description[]={
        "c(3 2 1) ",
        "c(2 1 1) ",
        "combo(c(3 2 1) )",
        "combo(c(2 1 1) c(3 2 1) )"
    };

    int i=0;
    for(auto it: medias){
        Media* m = it.second;
        DescriptionVisitor dv;
        m->accept(&dv);
        //cout<<dv.getDescription()<<endl;
        CHECK(description[i++] == dv.getDescription());
    }
}

#endif // UNITCOMMAND_H_INCLUDED


