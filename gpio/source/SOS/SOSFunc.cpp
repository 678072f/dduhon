//
//  SOSFunc.cpp
//  
//
//  Created by Daniel Duhon on 6/27/19.
//

#include "SOSFunc.h"
#include "GPIO.h"
#include <iostream>

using namespace std;

const int sDuration = 200000;
const int oDuration = 500000;

GPIOClass* gpio4 = new GPIOClass("4");

void s() {
    for(int i = 0; i < 3; i++) {
        cout << "." << endl;
        gpio4->setValGPIO("1");
        usleep(sDuration);
    }
}

void o() {
    for(int i = 0; i < 3; i++) {
        cout << "-" << endl;
        gpio4->setValGPIO("1");
        usleep(oDuration);
    }
    
}
