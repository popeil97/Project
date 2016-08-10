/* 
 * File:   Trainer.h
 * Author: fox2eagle1
 *
 * Created on July 20, 2016, 3:42 PM
 */

#ifndef TRAINER_H
#define	TRAINER_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include "NeuralNet.h"

using namespace std;


class Trainer { //allows user to train the neural net for their respected stock
private:
    int newCounter;
    int counter = 0;
    double max;
    vector<double> data; //holds all data values from text file
    ifstream dataTrainer;
    
public:
    Trainer(string file) {
        dataTrainer.open(file.c_str());
    }
    
    void getValues() {
        
        double value;
        dataTrainer >> value;
        
        max = value;
        while(dataTrainer.good()) { //reads values from text file and puts them in data vector
            if(value > max) {
                max = value;
                data.push_back(value);
                dataTrainer >> value;
            }
            
            else {
                data.push_back(value);
                dataTrainer >> value;
            }
            
            newCounter++;
            
        }
        
        //cout << "hello" << endl;
        
        for(unsigned i = 0; i < data.size(); i++) { //puts all stocks between 0 and 1
            data[i] = data[i]/max;
            cout << data[i] << " ";
        }
    }
    
    void print() { //this member function is only for testing
        for(unsigned i = 0; i < data.size(); i++) {
            cout << data[i] << " " ;
        }
        
        cout << endl;
    }
    
    bool atEnd() { //returns whether or not the trainer object is at the end of the text file
        if(counter == data.size()) {
            return true;
        }
        
        else
            return false;
    }
    void getInputAndTarget(vector <double> &input, vector <double> &target) { //empty vector initially
        input.clear();
        target.clear();
        int newCounter = counter;
        bool done = false;
        
        //puts target and input values in their respected vectors
        
        while(!done) {
            if(newCounter == counter + 1) {
                input.push_back(data[newCounter]);
            }
            
            if(newCounter == counter + 2) {
                input.push_back(data[newCounter]);
            }
            
            if(newCounter == counter + 3) {
                target.push_back(data[newCounter]);
                break;
            }
            
            newCounter++;
        }
        
        counter = newCounter;
        
    }
    
    bool counters() {
        if(newCounter % 3 == 0) {
            return true;
        }
        
        else {
            return false;
        }
    }
    
    double getMax() { //gets max so stock values will be between 0 and 1
        return max;
    }
    
    
};

#endif	/* TRAINER_H */

