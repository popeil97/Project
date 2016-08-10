/* 
 * File:   Stocks.h
 * Author: fox2eagle1
 *
 * Created on July 6, 2016, 3:28 PM
 */

#ifndef STOCKS_H
#define	STOCKS_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <cmath>

using namespace std;

class Stocks { //takes values from the net and make stock objects out of them
    
private:
    double value;
    string month;
    
public:
    
    Stocks(double value, string month) { //sets the month and value of the stock
        this->value = value;
        this->month = month;
    }
    
    void printStock() {
        cout << month << ": " << value << endl;
    }
    
    
};


#endif	/* STOCKS_H */

