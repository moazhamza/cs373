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
#include <set>

using namespace std;

// Transition tuple has current state int, input char, next state int

struct transition {
    int startState;
    char inputSymbol;
    int endState;
    
    transition(int x, char s, int y){
        this->startState = x;
        this->inputSymbol = s;
        this->endState = y;
    }
};

class configuration{
    public:
        int currentState;
        string inputString;
    
        configuration(int state, string str){
            currentState = state;
            inputString = str;
        }
    
    bool operator==(const configuration &other) const{
            return other.currentState == this->currentState && other.inputString == this->inputString;
        }
    bool operator!=(const configuration &other) const {
            return !(*this == other);
        }
    bool operator<(const configuration &other) const{
            if (other.currentState > this->currentState) return true;
            else return false;
        }
    
    
};


int startState;
vector<int> acceptStates;
vector<transition> transitions;

void stateParser(const string &line){
    if(line.at(8) == 's'){
        startState = atoi(&line.at(6));
    }
    if(line.at(8) == 'a'){
        acceptStates.push_back(atoi(&line.at(6)));
    }
}

void transitionParser(const string &line){
    transitions.push_back(transition(atoi(&line.at(11)), line.at(13), atoi(&line.at(15))));
}


bool checkInputRemains(const set<configuration> &configs){
    bool returnVal = false;
    
    for(configuration c : configs){
        if (c.inputString != "") returnVal = true;
    }
    
    return returnVal;
}

set<configuration> processConfigs(const set<configuration> &configs){
    set<configuration> newConfigs;
    for(configuration c : configs){
        int currState = c.currentState;
        string currString = c.inputString;
        char currInput = currString.at(0);
        
        for(size_t j=0; j < transitions.size(); j++){
            if(transitions[j].startState == currState
               && transitions[j].inputSymbol == currInput){
                
                int newState = transitions[j].endState;
                string newString = currString.substr(1);
                newConfigs.insert(configuration(newState, newString));
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
    set<configuration> allConfigs;
    allConfigs.insert(configuration(startState, argv[2]));
    
    
    
    while(checkInputRemains(allConfigs)){
        allConfigs = processConfigs(allConfigs);
        
    }
    
    bool accept = false;
    vector<int> finalStates;
    
    for (size_t i=0; i < acceptStates.size(); i++){
        for (configuration c : allConfigs){
            if (c.currentState == acceptStates[i]) {
                accept = true;
                finalStates.push_back(acceptStates[i]);
                break;
            }
        }
    }
    
    set<int> endStates;
    for(configuration c : allConfigs) endStates.insert( c.currentState );
    
    
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


