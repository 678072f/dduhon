# -*- Makefile -*-

all: Blinky GPIO SOLENOID

Blinky: Blinky.o GPIO.o
	g++ Blinky.o GPIO.o -o BLINKY

Blinky.o: Blinky.cpp
	g++ -c Blinky.cpp

GPIO: GPIO.o GPIOTest.o
	g++ GPIO.o GPIOTest.o -o GPIO

GPIOTest.o: GPIOTest.cpp
	g++ -c GPIOTest.cpp

SOLENOID: Solenoids.o GPIO.o
	g++ Solenoids.o GPIO.o -o SOLENOID

Solenoids.o: Solenoids.cpp
	g++ -c Solenoids.cpp

GPIO.o: GPIO.cpp GPIO.h
	g++ -c GPIO.cpp

clean:
	rm -rf *.o BLINKY GPIO SOLENOID
