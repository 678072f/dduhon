CC=g++

all: RPi

RPi: main.o GPIO.o
	$(CC) main.o GPIO.o -o RPi

main.o: main.cpp
	$(CC) -c main.cpp

GPIO.o: GPIO.cpp GPIO.h
	$(CC) -c GPIO.cpp

clean:
	rm -rf *.o RPi
