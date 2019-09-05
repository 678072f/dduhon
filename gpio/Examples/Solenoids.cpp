//
//  Solenoids.cpp
//  GPIO Class
//
//  Created by Daniel Duhon on 10/23/18.
//

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include "GPIO.h"
using namespace std;

void sigHandler(int sig);

bool ctrlCPressed = false;

int main(void)
{
    string inputState;
    struct sigaction sigStruct;
    sigStruct.sa_handler = sigHandler;
    sigStruct.sa_flags = 0;
    sigemptyset(&sigStruct.sa_mask);
    
    if (sigaction(SIGINT, &sigStruct, NULL) == -1) {
        cout << "Problem with sigaction" << endl;
        exit(1);
    }
    
    GPIOClass* gpio4 = new GPIOClass("4");
    GPIOClass* gpio17 = new GPIOClass("17");
    
    gpio4->exportGPIO();
    gpio17->exportGPIO();
    
    cout << "GPIO Pins exported....." << endl;
    
    gpio4->setDirGPIO("out");
    gpio17->setDirGPIO("in");
    
    cout << "Set GPIO pin directions" << endl;
    
    while (ctrlCPressed == false) {
        usleep(500000);
        gpio17->getValGPIO(inputState);
        if (inputState == "0") {
            cout << "Input state is " << inputState << endl;
            gpio4->setValGPIO("1");
            usleep(500000);
            gpio17->getValGPIO(inputState);
            if (inputState == "0") {
                cout << "Input state is " << inputState << endl;
                gpio4->setValGPIO("0");
            }
        }
    }
    
    if (ctrlCPressed == true) {
        cout << "Ctrl^C Pressed" << endl;
        cout << "Unexporting pins" << endl;
        gpio4->unexportGPIO();
        gpio17->unexportGPIO();
        cout << "Deallocating GPIO Objects" << endl;
        delete gpio4;
        gpio4 = 0;
        delete gpio17;
        gpio17 = 0;
    }
    cout << "Exiting....." << endl;
    return 0;
}

void sigHandler(int sig)
{
    write(0, "nCtrl^C pressed in sig handler", 32);
    ctrlCPressed = true;
}
