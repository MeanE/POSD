#include "TextUI.h"
#include <sstream>
#include <iostream>

string help(){
    ostringstream sout;
	sout << "This System Provide Some Instructions For User.\n"
        << "For Example:\n"
        << "\'def\' name = Shape(x,y,z,...) or name = combo{name,name}\n"
        << "\'name.area\' or \'name.perimeter\'\n"
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

}
