/* 
 * File:   main.cpp
 * Author: fox2eagle1
 *
 * Created on June 19, 2016, 2:55 PM
 */

#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include "NeuralNet.h"
#include "Trainer.h"
#include "UI.h"
#include "User.h"

using namespace std;

/*
 * 
 */

void printVector(string label,vector<double> &vector) {
    cout << label << " ";
    
    for(unsigned i = 0; i < vector.size(); i++) {
        cout << vector[i] << " ";
    }
    
    cout << endl;
}

void trainNet(string file, vector<double> &input, vector<double> &result, vector<double> &target, Net &myNet, double &maxValue) {
    Trainer trainer(file.c_str());
    trainer.getValues();
    //cout << endl << trainer.counters() << endl;
    
    while(true) {
       
        if(trainer.atEnd()) {
            break;
        }
        
        trainer.getInputAndTarget(input, target);
        
        myNet.feedForward(input);
        myNet.getResults(result);
        myNet.backProp(target);
        
        //cout << result[0] << " ";
        
    }
    
    maxValue = trainer.getMax();
    
    
    //cout << endl << trainer.counters() << endl;
    
    cout << endl << endl << "The Neural Net is trained for your specific stock!" << endl << endl;
}

double predictStock(vector<double> &values, vector<double> &target, vector<double> &results, Net &myNet) {
    cout << results.size() << endl;
    target.push_back(values.back());
    values.pop_back();
//    double aveOne = results[results.size()-2]; 
//    double aveTwo = results[results.size()-1];
//    double average = (aveTwo + aveOne)/7;
//    cout << average << endl;
    myNet.feedForward(values);
    myNet.getResults(results);
    myNet.backProp(target);
    
//    double aveOne = results[results.size()-2]; 
//    double aveTwo = results[results.size()-1];
//    double average = (aveTwo + aveOne)/7;
    //cout << results[0] + average;
    
    return results[0]; //+ average;
}

int main() {
    
    UI ui;
    User *user = nullptr; //pointer that will refer to the new user
    double maxValue = 1.0;
    
    vector<unsigned> architecture;
    
    architecture.push_back(2); //encapsulates the structure of the neural net
    architecture.push_back(4);
    architecture.push_back(1);
    
    Net myNet(architecture); //passes through the structure
    
    vector<double> inputValues;
    vector<double> targetValues;
    vector<double> resultValues;
    
//    int choice;
//    ui.display();
    
    while(true) { //displays user menu and handles choices
        
        int choice;
        ui.display();
        
        cout << "Choice?" << endl;
        cin >> choice;
        
        if(choice == 1) { //handles the training of the net
            string file;
            cout << "Please Enter File, with two input double values and one target" << endl;
            cin >> file;
            
           
            
            //trains the net for the respected file
            trainNet(file, inputValues, resultValues, targetValues, myNet, maxValue);
            
            
        }
        
        if(choice == 2) {
            user->showStocks(); //displays stocks
        }
        
        if(choice == 3) { //allows user to input specific past stock prices
            
            if(user == nullptr) { //must create user before net can predict stocks
                cout << "You need to create an account first" << endl;
                continue;
            }
            double inputOne;
            double inputTwo;
            double target;
            string month;
            
            cout << "Enter the past three month averages of stock prices for your respective stock" << endl;
            
            cin >> inputOne;
            cin >> inputTwo;
            cin >> target;
            cout << "What month are you trying to predict?" << endl;
            cin >> month;
            //cout << "hello";
            vector<double> values;
            
            values.push_back(inputOne/maxValue);
            values.push_back(inputTwo/maxValue);
            values.push_back(target/maxValue);
            
            double valueOfStock = abs(predictStock(values, targetValues, resultValues, myNet) * maxValue);
            cout << "The next month's value is " << valueOfStock << endl;
            user->addStock(valueOfStock, month);
            
            
            
            
        }
        
        if(choice == 4) { //allows user to create an account
            string username;
            //string lastName;
            cout << "What Do You Want Your Username to Be?" << endl;
            cin >> username;
            //getline(cin, username);
            
            user = new User();
            user->setUsername(username);
            //user->setLastName(lastName);
            
            cout << "Account Successfully Created" << endl;
        }
        
        if(choice == 5) { //allows user to exit the program
            cout << "Bye For Now!" << endl;
            exit(0);
        }
        
        else
            continue;
    }
   
    
    
    cout << endl;
    
    
    
    return 0;
}


