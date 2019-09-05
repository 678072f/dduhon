CC=g++

all: SOS

SOS: SOS.o SOSFunc.o GPIO.o
	$(CC) SOS.o SOSFunc.o GPIO.o -o SOS

SOS.o: SOS.cpp SOSFunc.cpp SOSFunc.h
	$(CC) -c SOS.cpp SOSFunc.cpp

GPIO.o: GPIO.cpp GPIO.h
	$(CC) -c GPIO.cpp

clean:
	rm -rf *.o SOS
