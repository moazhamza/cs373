//
//  main.cpp
//  programmingAssignment1
//
//  Created by Moaz Hamza on 1/24/17.
//  Copyright © 2017 Moaz Hamza. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <set>

using namespace std;

// Transition tuple has current state int, input char, next state int

struct transition {
    int startState;
    char inputSymbol;
    int endState;
    
    transition(int x, char s, int y){
        startState = x;
        inputSymbol = s;
        endState = y;
    }
};

struct configuration{
    int currentState;
    string inputString;
    
    configuration(int state, string str){
        currentState = state;
        inputString = str;
    }
};


int startState;
vector<int> acceptStates;
vector<transition> transitions;

void stateParser(string line){
    if(line.at(8) == 's'){
        startState = atoi(&line.at(6));
    }
    if(line.at(8) == 'a'){
        acceptStates.push_back(atoi(&line.at(6)));
    }
}

void transitionParser(string line){
    transitions.push_back(transition(atoi(&line.at(11)), line.at(13), atoi(&line.at(15))));
}

       


bool checkInputRemains(vector<configuration> configs){
    bool returnVal = false;
    
    for(int i=0; i < (int) configs.size(); i++){
        if (configs[i].inputString != "") returnVal = true;
    }
    
    return returnVal;
}

vector<configuration> processConfigs(vector<configuration> configs){
    vector<configuration> newConfigs;
    for(int i=0; i < (int)  configs.size(); i++){
        int currState = configs[i].currentState;
        string currString = configs[i].inputString;
        char currInput = currString.at(0);
        
        for(int j=0; j < (int) transitions.size(); j++){
            if(transitions[j].startState == currState
               && transitions[j].inputSymbol == currInput){
                
                int newState = transitions[j].endState;
                string newString = currString.substr(1);
                newConfigs.push_back(configuration(newState, newString));
            }
        }
    }
    return newConfigs;
}


int main(int argc, const char * argv[]) {
    string data;
    
    if (argc != 3){
        cout << "Please only include a file name and a string as arguments" << endl;
    }
    else{
        ifstream myfile(argv[1]);
        if (myfile.is_open()){
            while( getline(myfile, data) ){
                if (data.at(0) == 's'){
                    stateParser(data);
                }
                else{
                    transitionParser(data);
                }
            }
            // We should have all the data at this point. Can close the file
        }
        myfile.close();
    }

    vector<configuration> allConfigs;
    allConfigs.push_back(configuration(startState, argv[2]));
    
    bool accept = false;
    vector<int> finalStates;
    
    for (int i=0; i < (int) acceptStates.size(); i++){
        for (int j=0; j < (int) allConfigs.size(); j++){
            if (allConfigs[j].currentState == acceptStates[i]) {
                accept = true;
                finalStates.push_back(acceptStates[i]);
                break;
            }
        }
    }
    
    set<int> endStates;
    for( unsigned i = 0; i < allConfigs.size(); ++i ) endStates.insert( allConfigs[i].currentState );
    
    
    if(accept){
        cout << "accept ";
        for (int state : finalStates) cout << state << ' ';
        
        cout << endl;
    }
    else{
        cout << "reject ";
        for (int state : endStates) cout << state << ' ';
        cout << endl;
    }
    
    
    return 0;
}


