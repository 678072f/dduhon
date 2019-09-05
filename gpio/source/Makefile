CC=g++

all: Example

Example: Example.o GPIO.o
	$(CC) Example.o GPIO.o -o Example

Example.o: Example.cpp
	$(CC) -c Example.cpp

GPIO.o: GPIO.cpp GPIO.h
	$(CC) -c GPIO.cpp

clean:
	rm -rf *.o Example
