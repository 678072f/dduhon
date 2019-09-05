//
//  GPIO_<PROGRAM>.cpp
//  GPIO Class
//
//  Created by Daniel Duhon.
//

//Includes
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include "GPIO.h"
//-----------------

using namespace std;

//For stopping program, Press "Ctrl^C"
void sigHandler(int sig);

bool ctrlCPressed = false;

//Main Loop
int main(void)
{
    //Set up "sigHandler" (For detecting 'Ctrl^C' keypress)
    struct sigaction sigStruct;
    sigStruct.sa_handler = sigHandler;
    sigStruct.sa_flags = 0;
    sigemptyset(&sigStruct.sa_mask);
    
    if (sigaction(SIGINT, &sigStruct, NULL) == -1) {
        cout << "Problem with sigaction" << endl;
        exit(1);
    }
    
    //Set up pins to be used
    GPIOClass* gpio4 = new GPIOClass("4");
    
    //Export Pins
    gpio4->exportGPIO();
    //...
    
    cout << " GPIO pins exported " << endl;
    
    //Set input or output pins
    gpio4->setDirGPIO("out");
    
    cout << " Set GPIO pin directions " << endl;
    
    while(ctrlCPressed == false) //<- Usually: "ctrlCPressed == false"
    {
        //Here is where you write your program.
        //To write to the GPIO pins, use 'gpio<#>->setValGPIO("<Value>")'
        usleep(500000);
        gpio4->setValGPIO("1");
        cout << "ON" << endl;
        usleep(500000);
        gpio4->setValGPIO("0");
        cout << "OFF" << endl;
        
        //Tests whether 'Ctrl^C' is pressed and deletes pin values.
        if (ctrlCPressed == true) {
            cout << "Ctrl^C Pressed" << endl;
            cout << "Unexporting pins" << endl;
            gpio4->unexportGPIO();
            cout << "Deallocating GPIO Objects" << endl;
            
            //Repeat these two lines for each pin being used.
            delete gpio4;
            gpio4 = 0;
            
            break; //Breaks the program loop and exits the program
        }
    }
    
    cout << "Exiting....." << endl;
    return 0;
}

//Definition for sigHandler Function
void sigHandler(int sig)
{
    write(0, "nCtrl^C pressed in sig handler", 32);
    ctrlCPressed = true;
}
