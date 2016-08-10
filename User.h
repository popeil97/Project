/* 
 * File:   User.h
 * Author: fox2eagle1
 *
 * Created on July 6, 2016, 3:21 PM
 */

#ifndef USER_H
#define	USER_H


#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <cmath>
#include "Stocks.h"

using namespace std;

class User {
private:
    string username;
    bool signedIn = false; //user must be signed in to predict stock values
    vector<Stocks*> stocks; //holds pointers to predicted stocks
    
public:
    string getUsername() {
        return username;
    }
    
    void setUsername(string name) {
        username = name;
    }
    
    
    void printUser() { //used for testing
        cout << getUsername()  << endl;
    }
    
    void addStock(double num, string month) { //creates a stock object and adds it to the vector of stocks pointers
        Stocks* stocker = createStock(num, month);
        stocks.push_back(stocker);
    }
    
    Stocks* createStock(double value, string month) {
        Stocks* stock = new Stocks(value, month);
        return stock;
    }
    
    void showStocks() { //allows user to view the predictions the net has made
        
        cout << "Stocks for " << username << endl;
        
        for(int i = 0; i < stocks.size(); i++) {
            stocks[i]->printStock();
        }
    }
};


#endif	/* USER_H */

