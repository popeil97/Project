/* 
 * File:   UI.h
 * Author: fox2eagle1
 *
 * Created on July 21, 2016, 12:40 PM
 */

#ifndef UI_H
#define	UI_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <cmath>
#include <string>
#include <string.h>
#include "Trainer.h"

using namespace std;

class UI { //displays Main Menu
public:
    void display() {
        cout << "Welcome to StockPro!" << endl;
        cout << "--------------------" << endl;
        cout << opOne << endl;
        cout << opTwo << endl;
        cout << opThree << endl;
        cout << opFour << endl;
        cout << opFive << endl;
        cout << "--------------------" << endl;
    }
    
    
    
private:
    string opOne = "1. Train Net";
    string opTwo = "2. View Current Stocks";
    string opThree = "3. Enter New Stock Price";
    string opFour = "4. Create Account";
    string opFive = "5. Exit Program";
    
};

#endif	/* UI_H */

