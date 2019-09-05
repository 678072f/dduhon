//
//  GPIOTest.cpp
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
    
    //Set up pins
    string inputstate;
    GPIOClass* gpiox = new GPIOClass("x");
    GPIOClass* gpiox = new GPIOClass("x");
    
    gpiox->exportGPIO();
    gpiox->exportGPIO();
    
    cout << " GPIO pins exported" << endl;
    
    gpio17->setDirGPIO("in");
    gpio4->setDirGPIO("out");
    
    cout << " Set GPIO pin directions" << endl;
    
    while(1)
    {
        usleep(500000);
        gpio17->getValGPIO(inputstate);
        cout << "Current input pi state is " << inputstate << endl;
        if (inputstate == "0") {
            cout << "Input pin state is Pressed. Will check input pin state again in 20ms..." << endl;
            usleep(20000);
            cout << "Checking again ....." << endl;
            gpio17->getValGPIO(inputstate);
            if(inputstate == "0") {
                cout << "Input state is Pressed. Turning LED ON." << endl;
                gpio4->setValGPIO("1");
                
                cout << " Waiting until pin is unpressed....." << endl;
                while (inputstate == "0") {
                    gpio17->getValGPIO(inputstate);
                };
                cout << "Pin is unpressed" << endl;
            } else {
                cout << "Input pin state is UnPressed." << endl;
            }
        }
            gpio4->setValGPIO("0");
            
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
                break;
            }
        }
    cout << "Exiting....." << endl;
    return 0;
}

void sigHandler(int sig)
{
    write(0, "nCtrl^C pressed in sig handler", 32);
    ctrlCPressed = true;
}
