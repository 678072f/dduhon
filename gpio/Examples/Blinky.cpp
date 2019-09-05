//
//  Blinky.cpp
//  GPIO Class
//
//  Created by Daniel Duhon on 10/22/18.
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
int t;

int main(void)
{
    struct sigaction sigStruct;
    sigStruct.sa_handler = sigHandler;
    sigStruct.sa_flags = 0;
    sigemptyset(&sigStruct.sa_mask);
    
    if (sigaction(SIGINT, &sigStruct, NULL) == -1) {
        cout << "Problem with sigaction" << endl;
        exit(1);
    }
    
    GPIOClass* gpio4 = new GPIOClass("4");
    
    gpio4->exportGPIO();
    
    cout << "GPIO pins exported" << endl;
    
    gpio4->setDirGPIO("out");
    
    cout << "Set GPIO pin directions" << endl;
    cout << "Choose a blink interval in ms: " << endl;
    cin >> t;
    
    while(ctrlCPressed == false) {
        usleep(t);
        cout << "ON" << endl;
        gpio4->setValGPIO("1");
        usleep(t);
        cout << "OFF" << endl;
        gpio4->setValGPIO("0");
    }
    
    if (ctrlCPressed == true) {
        cout << "Ctrl^C Pressed" << endl;
        cout << "Unexporting pins" << endl;
        gpio4->unexportGPIO();
        cout << "Deallocating GPIO Objects" << endl;
        delete gpio4;
        gpio4 = 0;
    }
    cout << "Exiting....." << endl;
    return 0;
}

void sigHandler(int sig)
{
    write(0, "nCtrl^C pressed in sig handler", 32);
    ctrlCPressed = true;
}
